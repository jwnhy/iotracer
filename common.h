#include <linux/types.h>
struct ioctl_args {
  uint64_t pad;
  int syscall_nr;
  uint64_t fd;
  uint64_t cmd;
  char *arg;
};

struct ioctl_evt {
  uint64_t pid_tgid;
  uint64_t fd;
  uint64_t cmd;
  char *arg;
};

struct openat_args {
  uint64_t pad;
  int32_t syscall_nr;
  uint64_t dfd;
  const char *filename;
  int64_t flags;
  uint64_t mode;
};

struct openat_ret {
  uint64_t pad;
  int32_t syscall_nr;
  int64_t ret;
};

struct clone_ret {
  uint64_t pad;
  int32_t syscall_nr;
  int64_t ret;
};

