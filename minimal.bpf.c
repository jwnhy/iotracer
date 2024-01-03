// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
/* Copyright (c) 2020 Facebook */
#include <linux/types.h>
#include <bpf/bpf_helpers.h>
#include <linux/bpf.h>
#include <stdint.h>
#include "common.h"

char LICENSE[] SEC("license") = "Dual BSD/GPL";
int target_pid = 0;

struct {
  __uint(type, BPF_MAP_TYPE_HASH);
  __uint(max_entries, 256);
  __type(key, uint32_t);
  __type(value, uint8_t);
} target_set SEC(".maps");


struct {
  __uint(type, BPF_MAP_TYPE_HASH);
  __uint(max_entries, 32);
  __type(key, uint32_t);
  __type(value, uint32_t);
} opened_mali SEC(".maps");

struct {
  __uint(type, BPF_MAP_TYPE_RINGBUF);
  __uint(max_entries, 256 * 1024 /* 256 KB */);
} rb SEC(".maps");

int is_target(uint32_t pid) {
  if (pid == target_pid)
    return 1;
  return bpf_map_lookup_elem(&target_set, &pid) != NULL;
}


SEC("tp/syscalls/sys_enter_ioctl")
int ioctl_entry(struct ioctl_args *ctx) {
  uint64_t pid_tgid = bpf_get_current_pid_tgid();
  uint32_t pid = pid_tgid >> 32;
  uint32_t tgid = pid_tgid & 0xFFFFFFFF;
  uint32_t *dev_fd;
  struct ioctl_evt *rb_evt;

  // sanity checks: is it our target?
  if (!is_target(pid))
    return 0;

  dev_fd = bpf_map_lookup_elem(&opened_mali, &pid);
  // sanity checks: is dev a mali?
  if (!dev_fd || *dev_fd != ctx->fd)
    return 0;

  bpf_printk("PID: %d; TGID: %d\n", pid_tgid >> 32, pid_tgid && 0xFFFFFFFF);
  rb_evt = bpf_ringbuf_reserve(&rb, sizeof(struct ioctl_evt), 0);
  if (!rb_evt) {
    bpf_printk("ERROR: ringbuf_reserve failed;\n");
    return 1;
  }
  rb_evt->cmd = ctx->cmd;
  rb_evt->fd = ctx->fd;
  rb_evt->arg = ctx->arg;
  rb_evt->pid_tgid = pid_tgid;

  bpf_ringbuf_submit(rb_evt, 0);
  return 0;
}

int is_mali(const char * dev_name) {
  const char *mali = "/dev/mali0";
  if (!dev_name)
    return 0;
  for (int i = 0; i < 10; i++) {
    if (dev_name + i == NULL)
      return 0;
    if (dev_name[i] != mali[i]) {
      return 0;
    }
  }
  return 1;
}

SEC("tp/syscalls/sys_enter_openat")
int openat_entry(struct openat_args *ctx) {
  uint64_t pid_tgid = bpf_get_current_pid_tgid();
  uint32_t pid = pid_tgid >> 32;
  uint32_t tgid = pid_tgid & 0xFFFFFFFF;
  
  char filename[20];
  filename[19] = 0;

  if (bpf_probe_read_user_str(filename, 20, ctx->filename) < 0) {
    bpf_printk("ERROR: filename read failed;\n");
    return 0;
  }
  
  // the program is opening a mali dev
  if (is_mali(filename)) {
    //bpf_printk("PID: %d; TGID: %d\n", pid_tgid >> 32, pid_tgid && 0xFFFFFFFF);
    bpf_printk("%s\n", filename);
    uint32_t dev_fd = 0;
    bpf_map_update_elem(&opened_mali, &pid, &dev_fd, BPF_NOEXIST);
  }

  return 0;
}

SEC("tp/syscalls/sys_exit_openat")
int openat_exit(struct openat_ret *ctx) {
  uint64_t pid_tgid = bpf_get_current_pid_tgid();
  uint32_t pid = pid_tgid >> 32;
  uint32_t tgid = pid_tgid & 0xFFFFFFFF;
  // the program is opening a mali dev
  uint32_t *dev_fd = bpf_map_lookup_elem(&opened_mali, &pid);
  if (dev_fd && *dev_fd == 0) {
    bpf_printk("PID: %d, TGID: %d\n", pid, tgid);
    bpf_printk("assigning fd to mali: %d\n", ctx->ret);
    *dev_fd = ctx->ret;
  }
  return 0;
}

// tracing clone event
SEC("tp/syscalls/sys_exit_clone")
int clone_exit(struct clone_ret *ctx) {
  uint64_t pid_tgid = bpf_get_current_pid_tgid();
  uint32_t pid = pid_tgid >> 32;
  uint32_t tgid = pid_tgid & 0xFFFFFFFF;
  uint32_t child_pid = ctx->ret;
  // not target, break
  if (!is_target(pid))
    return 0;
  // the process have a opened mali dev?
  uint32_t *dev_fd = bpf_map_lookup_elem(&opened_mali, &pid);
  if (dev_fd) 
    bpf_map_update_elem(&opened_mali, &child_pid, dev_fd, BPF_NOEXIST);

  bpf_printk("CLONED: %d -> %d\n", pid, child_pid);
  // add newly born device to target 
  uint32_t dummy = 0;
  bpf_map_update_elem(&target_set, &child_pid, &dummy, BPF_NOEXIST); 
  return 0;
}
