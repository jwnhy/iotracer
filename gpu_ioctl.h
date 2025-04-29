#include "stdint.h"
struct nv_uuid {
  unsigned char uuid[16];
};
typedef struct {
  struct nv_uuid gpuUuid;
  unsigned int gpuMappingType;
  unsigned int gpuCachingType;
  unsigned int gpuFormatType;
  unsigned int gpuElementBits;
  unsigned int gpuCompressionType;
} UvmGpuMappingAttributes;

typedef struct {
  struct nv_uuid gpu_uuid;
  unsigned long long base_addr;
  unsigned long long dump_size;
  unsigned long long out_addr;
  unsigned int rmStatus;
} UVM_DUMP_GPU_MEMORY_PARAMS;
typedef struct {
  unsigned int rmStatus;
} UVM_CLEAN_UP_ZOMBIE_RESOURCES_PARAMS;
typedef struct {
  unsigned long long base;
  unsigned long long length;
  UvmGpuMappingAttributes perGpuAttributes[256];
  unsigned long long gpuAttributesCount;
  unsigned int rmStatus;
} UVM_ALLOC_SEMAPHORE_POOL_PARAMS;
typedef struct {
  unsigned long long rangeGroupId;
  struct nv_uuid destinationUuid;
  unsigned int rmStatus;
} UVM_MIGRATE_RANGE_GROUP_PARAMS;
typedef struct {
  unsigned long long base;
  unsigned long long length;
  struct nv_uuid gpuUuid;
  unsigned int rmStatus;
} UVM_MAP_DYNAMIC_PARALLELISM_REGION_PARAMS;
typedef struct {
  unsigned long long base;
  unsigned long long length;
  struct nv_uuid gpuUuid;
  unsigned int rmStatus;
} UVM_UNMAP_EXTERNAL_PARAMS;
typedef struct {
  unsigned long long buffer;
  unsigned long long size;
  unsigned long long targetVa;
  unsigned long long bytesWritten;
  unsigned int rmStatus;
} UVM_TOOLS_WRITE_PROCESS_MEMORY_PARAMS;
typedef struct {
  struct nv_uuid gpu_uuid;
  unsigned int rmStatus;
} UVM_ENABLE_SYSTEM_WIDE_ATOMICS_PARAMS;
typedef struct {
  unsigned long long base;
  unsigned long long length;
  struct nv_uuid destinationUuid;
  unsigned int flags;
  unsigned long long semaphoreAddress;
  unsigned int semaphorePayload;
  int cpuNumaNode;
  unsigned long long userSpaceStart;
  unsigned long long userSpaceLength;
  unsigned int rmStatus;
} UVM_MIGRATE_PARAMS;
typedef struct {
  struct nv_uuid gpuUuidA;
  struct nv_uuid gpuUuidB;
  unsigned int rmStatus;
} UVM_ENABLE_PEER_ACCESS_PARAMS;
typedef struct {
  unsigned long long base;
  unsigned long long length;
  unsigned int rmStatus;
} UVM_CREATE_EXTERNAL_RANGE_PARAMS;
typedef struct {
  unsigned long long rangeGroupId;
  unsigned int rmStatus;
} UVM_DESTROY_RANGE_GROUP_PARAMS;
typedef struct {
  struct nv_uuid gpu_uuid;
  unsigned int rmStatus;
} UVM_DISABLE_SYSTEM_WIDE_ATOMICS_PARAMS;
typedef struct {
  unsigned long long base;
  unsigned long long length;
  unsigned long long offset;
  UvmGpuMappingAttributes perGpuAttributes[256];
  unsigned long long gpuAttributesCount;
  int rmCtrlFd;
  unsigned int hClient;
  unsigned int hMemory;
  unsigned int rmStatus;
} UVM_MAP_EXTERNAL_ALLOCATION_PARAMS;
typedef struct {
  unsigned long long base;
  unsigned long long length;
  unsigned int rmStatus;
} UVM_FREE_PARAMS;
typedef struct {
  struct nv_uuid gpu_uuid;
  unsigned char pageableMemAccess;
  unsigned int rmStatus;
} UVM_PAGEABLE_MEM_ACCESS_ON_GPU_PARAMS;
typedef struct {
  struct nv_uuid gpu_uuid;
  unsigned int rmStatus;
} UVM_UNREGISTER_GPU_PARAMS;
typedef struct {
  unsigned long long buffer;
  unsigned long long size;
  unsigned long long targetVa;
  unsigned long long bytesRead;
  unsigned int rmStatus;
} UVM_TOOLS_READ_PROCESS_MEMORY_PARAMS;
typedef struct {
  unsigned long long requestedBase;
  unsigned long long length;
  struct nv_uuid accessedByUuid;
  unsigned int rmStatus;
} UVM_SET_ACCESSED_BY_PARAMS;
typedef struct {
  unsigned long long tablePtr;
  unsigned int rmStatus;
} UVM_TOOLS_GET_PROCESSOR_UUID_TABLE_PARAMS;
typedef struct {
  unsigned char pageableMemAccess;
  unsigned int rmStatus;
} UVM_PAGEABLE_MEM_ACCESS_PARAMS;
typedef struct {
  unsigned long long rangeGroupId;
  unsigned int rmStatus;
} UVM_CREATE_RANGE_GROUP_PARAMS;
typedef struct {
  struct nv_uuid gpuUuid;
  int rmCtrlFd;
  unsigned int hClient;
  unsigned int hChannel;
  unsigned long long base;
  unsigned long long length;
  unsigned int rmStatus;
} UVM_REGISTER_CHANNEL_PARAMS;
typedef struct {
  unsigned long long flags;
  unsigned int rmStatus;
} UVM_INITIALIZE_PARAMS;
typedef struct {
  unsigned int rmStatus;
} UVM_CLEAR_ALL_ACCESS_COUNTERS_PARAMS;
typedef struct {
  unsigned long long base;
  unsigned long long length;
  unsigned long long offset;
  struct nv_uuid gpuUuid;
  int rmCtrlFd;
  unsigned int hClient;
  unsigned int hMemory;
  unsigned int rmStatus;
} UVM_ALLOC_DEVICE_P2P_PARAMS;
typedef struct {
  unsigned long long rangeGroupId;
  unsigned long long requestedBase;
  unsigned long long length;
  unsigned int rmStatus;
} UVM_SET_RANGE_GROUP_PARAMS;
typedef struct {
  int uvmFd;
  unsigned int rmStatus;
} UVM_MM_INITIALIZE_PARAMS;
typedef struct {
  unsigned long long base;
  unsigned long long length;
  struct nv_uuid gpuUuid;
  unsigned int rmStatus;
} UVM_MAP_EXTERNAL_SPARSE_PARAMS;
typedef struct {
  unsigned long long base;
  unsigned long long length;
  unsigned int rmStatus;
} UVM_VALIDATE_VA_RANGE_PARAMS;
typedef struct {
  struct nv_uuid gpu_uuid;
  unsigned char numaEnabled;
  int numaNodeId;
  int rmCtrlFd;
  unsigned int hClient;
  unsigned int hSmcPartRef;
  unsigned int rmStatus;
} UVM_REGISTER_GPU_PARAMS;
typedef struct {
  unsigned long long rangeGroupIds[32];
  unsigned long long numGroupIds;
  unsigned int rmStatus;
} UVM_PREVENT_MIGRATION_RANGE_GROUPS_PARAMS;
typedef struct {
  unsigned long long rangeGroupIds[32];
  unsigned long long numGroupIds;
  unsigned int rmStatus;
} UVM_ALLOW_MIGRATION_RANGE_GROUPS_PARAMS;
typedef struct {
  struct nv_uuid gpuUuidA;
  struct nv_uuid gpuUuidB;
  unsigned int rmStatus;
} UVM_DISABLE_PEER_ACCESS_PARAMS;
typedef struct {
  struct nv_uuid gpuUuid;
  unsigned int rmStatus;
} UVM_UNREGISTER_GPU_VASPACE_PARAMS;
typedef struct {
  unsigned long long requestedBase;
  unsigned long long length;
  struct nv_uuid preferredLocation;
  int preferredCpuNumaNode;
  unsigned int rmStatus;
} UVM_SET_PREFERRED_LOCATION_PARAMS;
typedef struct {
  unsigned long long requestedBase;
  unsigned long long length;
  unsigned int rmStatus;
} UVM_UNSET_PREFERRED_LOCATION_PARAMS;
typedef struct {
  unsigned long long requestedBase;
  unsigned long long length;
  struct nv_uuid accessedByUuid;
  unsigned int rmStatus;
} UVM_UNSET_ACCESSED_BY_PARAMS;
typedef struct {
  struct nv_uuid gpuUuid;
  unsigned int hClient;
  unsigned int hChannel;
  unsigned int rmStatus;
} UVM_UNREGISTER_CHANNEL_PARAMS;
typedef struct {
  struct nv_uuid gpuUuid;
  int rmCtrlFd;
  unsigned int hClient;
  unsigned int hVaSpace;
  unsigned int rmStatus;
} UVM_REGISTER_GPU_VASPACE_PARAMS;
typedef struct {
  unsigned int rmStatus;
} UVM_TOOLS_FLUSH_EVENTS_PARAMS;
typedef struct {
  unsigned long long requestedBase;
  unsigned long long length;
  unsigned int rmStatus;
} UVM_DISABLE_READ_DUPLICATION_PARAMS;
typedef struct {
  unsigned long long base;
  unsigned long long length;
  unsigned int flags;
  unsigned int rmStatus;
} UVM_POPULATE_PAGEABLE_PARAMS;
typedef struct {
  unsigned long long requestedBase;
  unsigned long long length;
  unsigned int rmStatus;
} UVM_ENABLE_READ_DUPLICATION_PARAMS;
static inline uint64_t sizeofarg(int cmd) {
  switch (cmd) {
  case 805306369:
    return sizeof(UVM_INITIALIZE_PARAMS);
  case 75:
    return sizeof(UVM_MM_INITIALIZE_PARAMS);
  case 39:
    return sizeof(UVM_PAGEABLE_MEM_ACCESS_PARAMS);
  case 70:
    return sizeof(UVM_PAGEABLE_MEM_ACCESS_ON_GPU_PARAMS);
  case 37:
    return sizeof(UVM_REGISTER_GPU_PARAMS);
  case 38:
    return sizeof(UVM_UNREGISTER_GPU_PARAMS);
  case 23:
    return sizeof(UVM_CREATE_RANGE_GROUP_PARAMS);
  case 24:
    return sizeof(UVM_DESTROY_RANGE_GROUP_PARAMS);
  case 29:
    return sizeof(UVM_ENABLE_PEER_ACCESS_PARAMS);
  case 30:
    return sizeof(UVM_DISABLE_PEER_ACCESS_PARAMS);
  case 31:
    return sizeof(UVM_SET_RANGE_GROUP_PARAMS);
  case 73:
    return sizeof(UVM_CREATE_EXTERNAL_RANGE_PARAMS);
  case 33:
    return sizeof(UVM_MAP_EXTERNAL_ALLOCATION_PARAMS);
  case 74:
    return sizeof(UVM_MAP_EXTERNAL_SPARSE_PARAMS);
  case 34:
    return sizeof(UVM_FREE_PARAMS);
  case 40:
    return sizeof(UVM_PREVENT_MIGRATION_RANGE_GROUPS_PARAMS);
  case 41:
    return sizeof(UVM_ALLOW_MIGRATION_RANGE_GROUPS_PARAMS);
  case 42:
    return sizeof(UVM_SET_PREFERRED_LOCATION_PARAMS);
  case 43:
    return sizeof(UVM_UNSET_PREFERRED_LOCATION_PARAMS);
  case 46:
    return sizeof(UVM_SET_ACCESSED_BY_PARAMS);
  case 47:
    return sizeof(UVM_UNSET_ACCESSED_BY_PARAMS);
  case 25:
    return sizeof(UVM_REGISTER_GPU_VASPACE_PARAMS);
  case 26:
    return sizeof(UVM_UNREGISTER_GPU_VASPACE_PARAMS);
  case 27:
    return sizeof(UVM_REGISTER_CHANNEL_PARAMS);
  case 28:
    return sizeof(UVM_UNREGISTER_CHANNEL_PARAMS);
  case 44:
    return sizeof(UVM_ENABLE_READ_DUPLICATION_PARAMS);
  case 45:
    return sizeof(UVM_DISABLE_READ_DUPLICATION_PARAMS);
  case 51:
    return sizeof(UVM_MIGRATE_PARAMS);
  case 54:
    return sizeof(UVM_ENABLE_SYSTEM_WIDE_ATOMICS_PARAMS);
  case 55:
    return sizeof(UVM_DISABLE_SYSTEM_WIDE_ATOMICS_PARAMS);
  case 62:
    return sizeof(UVM_TOOLS_READ_PROCESS_MEMORY_PARAMS);
  case 63:
    return sizeof(UVM_TOOLS_WRITE_PROCESS_MEMORY_PARAMS);
  case 64:
    return sizeof(UVM_TOOLS_GET_PROCESSOR_UUID_TABLE_PARAMS);
  case 65:
    return sizeof(UVM_MAP_DYNAMIC_PARALLELISM_REGION_PARAMS);
  case 66:
    return sizeof(UVM_UNMAP_EXTERNAL_PARAMS);
  case 53:
    return sizeof(UVM_MIGRATE_RANGE_GROUP_PARAMS);
  case 67:
    return sizeof(UVM_TOOLS_FLUSH_EVENTS_PARAMS);
  case 68:
    return sizeof(UVM_ALLOC_SEMAPHORE_POOL_PARAMS);
  case 69:
    return sizeof(UVM_CLEAN_UP_ZOMBIE_RESOURCES_PARAMS);
  case 71:
    return sizeof(UVM_POPULATE_PAGEABLE_PARAMS);
  case 72:
    return sizeof(UVM_VALIDATE_VA_RANGE_PARAMS);
  case 77:
    return sizeof(UVM_TOOLS_GET_PROCESSOR_UUID_TABLE_PARAMS);
  case 78:
    return sizeof(UVM_ALLOC_DEVICE_P2P_PARAMS);
  case 79:
    return sizeof(UVM_CLEAR_ALL_ACCESS_COUNTERS_PARAMS);
  case 111:
    return sizeof(UVM_DUMP_GPU_MEMORY_PARAMS);
  default:
    return 0;
  }
}

