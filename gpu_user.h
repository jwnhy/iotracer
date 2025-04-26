#include "gpu_ioctl.h"
#include <stdint.h>
#include <stdio.h>
static inline uint64_t cmdname(uint64_t cmd, uint64_t arg) {
  switch (cmd) {
  case UVM_CREATE_EXTERNAL_RANGE:
    return (uint64_t)"UVM_CREATE_EXTERNAL_RANGE\n";
  case UVM_MAP_EXTERNAL_ALLOCATION:
    return (uint64_t)"UVM_MAP_EXTERNAL_ALLOCATION\n";
  }
  return 0;
}
static inline uint64_t printerofarg(uint64_t cmd, uint64_t arg) {
  switch (cmd) {
  case UVM_CREATE_EXTERNAL_RANGE: {
    UVM_CREATE_EXTERNAL_RANGE_PARAMS *params =
        (UVM_CREATE_EXTERNAL_RANGE_PARAMS *)arg;
    printf("base: %llx\n", params->base);
    printf("length: %llx\n", params->length);
  } break;
  case UVM_MAP_EXTERNAL_ALLOCATION: {
    UVM_MAP_EXTERNAL_ALLOCATION_PARAMS *params =
        (UVM_MAP_EXTERNAL_ALLOCATION_PARAMS *)arg;
    printf("base: %llx\n", params->base);
    printf("length: %llx\n", params->length);
    printf("offset: %llx\n", params->offset);
    printf("attrCnt: %d\n", params->attrCnt);
    printf("rmCtrlFd: %d\n", params->rmCtrlFd);
    printf("hClient: %d\n", params->hClient);
    printf("hMemory: %d\n", params->hMemory);
  } break;
  }
  return 0;
}
static inline uint64_t printerofret(uint64_t cmd, uint64_t arg) {
  switch (cmd) {
  case UVM_CREATE_EXTERNAL_RANGE: {
    UVM_CREATE_EXTERNAL_RANGE_PARAMS *params =
        (UVM_CREATE_EXTERNAL_RANGE_PARAMS *)arg;
    printf("status: %d\n", params->status);
  } break;
  case UVM_MAP_EXTERNAL_ALLOCATION: {
    UVM_MAP_EXTERNAL_ALLOCATION_PARAMS *params =
        (UVM_MAP_EXTERNAL_ALLOCATION_PARAMS *)arg;
    printf("status: %d\n", params->status);
  } break;
  }
  return 0;
}
