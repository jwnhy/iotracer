
#include <stdint.h>

#define UVM_CREATE_EXTERNAL_RANGE 73

typedef struct {
  uint64_t base;
  uint64_t length;

  uint32_t status;
} UVM_CREATE_EXTERNAL_RANGE_PARAMS;

#define UVM_MAP_EXTERNAL_ALLOCATION 33

typedef struct {
  uint8_t uuid[16];
  uint32_t mapType;
  uint32_t cachingType;
  uint32_t formatType;
  uint32_t elemBits;
  uint32_t compressType;
} UvmGpuMapAttr;

typedef struct {
  uint64_t base;
  uint64_t length;
  uint64_t offset;
  UvmGpuMapAttr perGpuAttr[256];
  uint32_t attrCnt;
  int32_t rmCtrlFd;
  uint32_t hClient;
  uint32_t hMemory;

  uint32_t status;
} UVM_MAP_EXTERNAL_ALLOCATION_PARAMS;
