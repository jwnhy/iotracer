#include <assert.h>
#include <bpf/libbpf.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#include "common.h"

struct ring_buffer *global_rb;

static int libbpf_print_fn(enum libbpf_print_level level, const char *format,
                           va_list args) {
  return vfprintf(stderr, format, args);
}

int handle_mali_evt(void *ctx, void *data, size_t data_sz) {
  const struct ioctl_evt *evt = data;
  const pid_t pid = evt->pid_tgid >> 32;
  //const pid_t tgid = evt->pid_tgid & 0xFFFFFFFF;
  printf("MALI OP: %d, %lu, 0x%lx\n", pid, evt->cmd, (unsigned long)evt->arg);
  return 0;

}

struct minimal_bpf *load_bpf_tracer(pid_t target_pid) {
  int ret;
  struct minimal_bpf *skel;
  // libbpf_set_print(libbpf_print_fn);

  skel = minimal_bpf__open();
  if (!skel) {
    fprintf(stderr, "Failed to open BPF skeleton\n");
    exit(1);
  }

  skel->bss->target_pid= target_pid;

  ret = minimal_bpf__load(skel);
  if (ret) {
    fprintf(stderr, "Failed to load and verify BPF skeleton\n");
    goto cleanup;
  }

  ret = minimal_bpf__attach(skel);
  if (ret) {
    fprintf(stderr, "Failed to attach BPF skeleton\n");
    goto cleanup;
  }

  global_rb = ring_buffer__new(bpf_map__fd(skel->maps.rb), handle_mali_evt, NULL, NULL);
	if (!global_rb) {
		ret = -1;
		fprintf(stderr, "Failed to create ring buffer\n");
		goto cleanup;
	}
  return skel;

cleanup:
  minimal_bpf__destroy(skel);
  exit(-ret);
}

int main(int argc, char **argv) {
  pid_t pid;
  struct minimal_bpf *skel;
  sem_t *sem_p;
  sem_p = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE,
               MAP_ANONYMOUS | MAP_SHARED, 0, 0);
  assert(sem_p != MAP_FAILED);
  sem_init(sem_p, 1, 0);

  if (argc < 2) {
    fprintf(stderr, "Usage: ./iotracer <CMD> <ARGS>");
    return 1;
  }
  pid = fork();
  assert(pid != -1);
  if (pid == 0) {
    sem_wait(sem_p);
    printf("Child is execing the target\n");
    execv(argv[1], &argv[1]);
  } else {
    printf("Child PID is %d;\n", pid);
    printf("Loading BPF program\n");
    skel = load_bpf_tracer(pid);
    printf("Complete, starting target program\n");
    msync(sem_p, sizeof(sem_t), MS_SYNC);
    sem_post(sem_p);
    while(waitpid(pid, NULL, WNOHANG) == 0) {
      ring_buffer__poll(global_rb, 100 /* timeout, ms */);
    }
    minimal_bpf__destroy(skel);
  }
}
