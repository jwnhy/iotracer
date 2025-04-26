// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
/* Copyright (c) 2020 Facebook */
#include "common.h"
#include "gpu_bpf.h"
#include <linux/bpf.h>
#include <linux/types.h>
#include <stdint.h>
#include <bpf/bpf_helpers.h>
char LICENSE[] SEC("license") = "Dual BSD/GPL";
int target_pid = 0;

struct {
  __uint(type, BPF_MAP_TYPE_HASH);
  __uint(max_entries, 32);
  __type(key, uint32_t);
  __type(value, struct ioctl_ongoing);
} ongoing_ioctl SEC(".maps");

struct {
  __uint(type, BPF_MAP_TYPE_HASH);
  __uint(max_entries, 256);
  __type(key, uint32_t);
  __type(value, uint8_t);
} target_set SEC(".maps");

struct nvidia_dev_t {
  uint32_t pid;
  uint32_t fd;
  char filename[30];
  uint8_t found;
};

struct {
  __uint(type, BPF_MAP_TYPE_ARRAY);
  __uint(max_entries, 32);
  __type(key, uint32_t);
  __type(value, struct nvidia_dev_t);
} opened_nvidia SEC(".maps");

struct {
  __uint(type, BPF_MAP_TYPE_RINGBUF);
  __uint(max_entries, 256 * 1024 /* 256 KB */);
} rb SEC(".maps");

int is_target(uint32_t pid) {
  if (pid == target_pid)
    return 1;
  return bpf_map_lookup_elem(&target_set, &pid) != NULL;
}

static int lookup_dev(uint32_t nr, struct nvidia_dev_t *ctx) {
  struct nvidia_dev_t *dev = bpf_map_lookup_elem(&opened_nvidia, &nr);
  if (dev)
    bpf_printk("nr: %d, fd %d, pid %d\n", nr, dev->fd, dev->pid);
  if (dev && dev->fd == ctx->fd && dev->pid == ctx->pid) {
    *ctx = *dev;
    ctx->found = 1;
    return 1;
  }
  return 0;
}

SEC("tp/syscalls/sys_exit_ioctl")
int ioctl_exit(struct ioctl_ret *ctx) {
  uint64_t pid_tgid = bpf_get_current_pid_tgid();
  uint32_t pid = pid_tgid >> 32, tgid = pid_tgid & 0xFFFFFFFF;
  uint32_t retsize;
  struct ioctl_evt *rb_evt;

  return 0;
}

SEC("tp/syscalls/sys_enter_ioctl")
int ioctl_entry(struct ioctl_args *ctx) {
  uint64_t pid_tgid = bpf_get_current_pid_tgid();
  uint32_t pid = pid_tgid >> 32, tgid = pid_tgid & 0xFFFFFFFF;
  uint32_t argsize;
  uint32_t *dev_fd;
  struct nvidia_dev_t dev = {
      .pid = pid,
      .fd = ctx->fd,
      .found = 0,
  };
  struct ioctl_evt *rb_evt;

  // sanity checks: is it our target?
  if (!is_target(pid))
    return 0;
  bpf_printk("target pid: %d\n", pid);
  bpf_loop(32, lookup_dev, &dev, 0);
  if (!dev.found)
    return 0;
  bpf_printk("device found");

  argsize = sizeofparam(ctx->cmd, 0);
  rb_evt = bpf_ringbuf_reserve(&rb, sizeof(struct ioctl_evt) + argsize, 0);
  if (!rb_evt) {
    bpf_printk("ERROR: ringbuf reserve failed;\n");
    return 0;
  }
  rb_evt->cmd = ctx->cmd;
  rb_evt->fd = ctx->fd;
  rb_evt->pid_tgid = pid_tgid;
  rb_evt->diretion = CPUTOGPU;
  bpf_probe_read_user(rb_evt->data, argsize, ctx->arg);
  bpf_ringbuf_submit(rb_evt, 0);
  return 0;
}

int is_nvidia(const char *dev_name) {
  const char *mali[3] = {"/dev/nvidia-uvm", "/dev/nvidia0", "/dev/nvidiactl"};
  if (!dev_name)
    return 0;
  for (int i = 0; i < 3; i++) {
    if (bpf_strncmp(dev_name, 30, mali[i]) == 0)
      return 1;
  }
  return 0;
}

static int insert_dev(uint32_t nr, struct nvidia_dev_t *dev) {
  struct nvidia_dev_t *slot = bpf_map_lookup_elem(&opened_nvidia, &nr);
  if (slot && slot->found == 0) {
    bpf_map_update_elem(&opened_nvidia, &nr, dev, BPF_ANY);
    return 1;
  }
  return 0;
}

SEC("tp/syscalls/sys_enter_openat")
int openat_entry(struct openat_args *ctx) {
  uint64_t pid_tgid = bpf_get_current_pid_tgid();
  uint32_t pid = pid_tgid >> 32;
  uint32_t tgid = pid_tgid & 0xFFFFFFFF;

  struct nvidia_dev_t dev = {
      .pid = pid,
      .fd = -1,
  };
  if (bpf_probe_read_user_str(dev.filename, 30, ctx->filename) < 0) {
    bpf_printk("ERROR: filename read failed;\n");
    return 0;
  }

  // the program is opening a mali dev
  if (is_nvidia(dev.filename)) {
    // bpf_printk("PID: %d; TGID: %d\n", pid_tgid >> 32, pid_tgid &&
    // 0xFFFFFFFF);
    bpf_printk("%s\n", dev.filename);
    bpf_loop(32, insert_dev, &dev, 0);
  }
  return 0;
}

struct pidfd {
  uint32_t pid;
  uint32_t fd;
};

static int update_dev_fd(uint32_t nr, struct pidfd *pf) {
  struct nvidia_dev_t *dev = bpf_map_lookup_elem(&opened_nvidia, &nr);
  if (dev && dev->pid == pf->pid && dev->fd == -1) {
    dev->fd = pf->fd;
    bpf_map_update_elem(&opened_nvidia, &nr, dev, BPF_ANY);
    return 1;
  }
  return 0;
}

SEC("tp/syscalls/sys_exit_openat")
int openat_exit(struct openat_ret *ctx) {
  uint64_t pid_tgid = bpf_get_current_pid_tgid();
  uint32_t pid = pid_tgid >> 32;
  uint32_t tgid = pid_tgid & 0xFFFFFFFF;
  struct pidfd pf = {
      .pid = pid,
      .fd = ctx->ret,
  };

  bpf_loop(32, update_dev_fd, &pf, 0);
  return 0;
}

struct pidpid {
  uint32_t pid;
  uint32_t child_pid;
};

static int clone_dev(uint32_t nr, struct pidpid *pp) {
  struct nvidia_dev_t *dev = bpf_map_lookup_elem(&opened_nvidia, &nr);
  if (dev && dev->pid == pp->pid) {
    struct nvidia_dev_t new_dev = *dev;
    new_dev.pid = pp->child_pid;
    bpf_loop(32, insert_dev, &new_dev, 0);
    return 1;
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
  struct pidpid pp = {
      .pid = pid,
      .child_pid = child_pid,
  };
  bpf_loop(32, clone_dev, &pp, 0);

  bpf_printk("CLONED: %d -> %d\n", pid, child_pid);
  // add newly born process to target
  uint32_t dummy = 0;
  bpf_map_update_elem(&target_set, &child_pid, &dummy, BPF_NOEXIST);
  return 0;
}
