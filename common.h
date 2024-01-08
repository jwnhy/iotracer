#include <stdint.h>
#define CPUTOGPU 1
#define GPUTOCPU 2

struct ioctl_ret {
  uint64_t pad;
  int32_t syscall_nr;
  int64_t ret;
};

struct ioctl_args {
  uint64_t pad;
  int syscall_nr;
  uint64_t fd;
  uint64_t cmd;
  char *arg;
};

struct ioctl_ongoing {
  uint64_t fd;
  uint64_t cmd;
  char *data;
};

struct ioctl_evt {
  uint64_t pid_tgid;
  uint64_t fd;
  uint64_t cmd;
  uint8_t diretion;
  char data[0];
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

