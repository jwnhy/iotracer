#include "stdint.h"
#include "gpu_ioctl.h"
static inline uint64_t sizeofparam(uint64_t cmd, uint64_t arg) {
  switch(cmd) {
    case UVM_CREATE_EXTERNAL_RANGE:
      return sizeof(UVM_CREATE_EXTERNAL_RANGE_PARAMS);
    case UVM_MAP_EXTERNAL_ALLOCATION:
      return sizeof(UVM_MAP_EXTERNAL_ALLOCATION_PARAMS);
  }
 return 0;
}
