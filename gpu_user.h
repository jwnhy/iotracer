#include "gpu_ioctl.h"
#include <stdint.h>
#include <stdio.h>

static inline void printer_struct_nv_uuid(struct nv_uuid *obj) {
  printf("struct nv_uuid {\n");
  printf("obj->uuid: %s\n", obj->uuid);
  printf("}\n");
}

static inline void
printer_UvmGpuMappingAttributes(UvmGpuMappingAttributes *obj) {
  printf("UvmGpuMappingAttributes {\n");
  printf("obj->gpuUuid:\n");
  printer_struct_nv_uuid(&(obj->gpuUuid));
  printf("obj->gpuMappingType: 0x%lx\n", obj->gpuMappingType);
  printf("obj->gpuCachingType: 0x%lx\n", obj->gpuCachingType);
  printf("obj->gpuFormatType: 0x%lx\n", obj->gpuFormatType);
  printf("obj->gpuElementBits: 0x%lx\n", obj->gpuElementBits);
  printf("obj->gpuCompressionType: 0x%lx\n", obj->gpuCompressionType);
  printf("}\n");
}

static inline void
printer_UVM_DUMP_GPU_MEMORY_PARAMS(UVM_DUMP_GPU_MEMORY_PARAMS *obj) {
  printf("UVM_DUMP_GPU_MEMORY_PARAMS {\n");
  printf("obj->gpu_uuid:\n");
  printer_struct_nv_uuid(&(obj->gpu_uuid));
  printf("obj->base_addr: 0x%lx\n", obj->base_addr);
  printf("obj->dump_size: 0x%lx\n", obj->dump_size);
  printf("obj->out_addr: 0x%lx\n", obj->out_addr);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_CLEAN_UP_ZOMBIE_RESOURCES_PARAMS(
    UVM_CLEAN_UP_ZOMBIE_RESOURCES_PARAMS *obj) {
  printf("UVM_CLEAN_UP_ZOMBIE_RESOURCES_PARAMS {\n");
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_ALLOC_SEMAPHORE_POOL_PARAMS(UVM_ALLOC_SEMAPHORE_POOL_PARAMS *obj) {
  printf("UVM_ALLOC_SEMAPHORE_POOL_PARAMS {\n");
  printf("obj->base: 0x%lx\n", obj->base);
  printf("obj->length: 0x%lx\n", obj->length);
  for (uint64_t i = 0; i < 1; ++i) {
    printf("obj->perGpuAttributes[i]:\n");
    printer_UvmGpuMappingAttributes(&(obj->perGpuAttributes[i]));
  }
  printf("obj->gpuAttributesCount: 0x%lx\n", obj->gpuAttributesCount);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_MIGRATE_RANGE_GROUP_PARAMS(UVM_MIGRATE_RANGE_GROUP_PARAMS *obj) {
  printf("UVM_MIGRATE_RANGE_GROUP_PARAMS {\n");
  printf("obj->rangeGroupId: 0x%lx\n", obj->rangeGroupId);
  printf("obj->destinationUuid:\n");
  printer_struct_nv_uuid(&(obj->destinationUuid));
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_MAP_DYNAMIC_PARALLELISM_REGION_PARAMS(
    UVM_MAP_DYNAMIC_PARALLELISM_REGION_PARAMS *obj) {
  printf("UVM_MAP_DYNAMIC_PARALLELISM_REGION_PARAMS {\n");
  printf("obj->base: 0x%lx\n", obj->base);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->gpuUuid:\n");
  printer_struct_nv_uuid(&(obj->gpuUuid));
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_UNMAP_EXTERNAL_PARAMS(UVM_UNMAP_EXTERNAL_PARAMS *obj) {
  printf("UVM_UNMAP_EXTERNAL_PARAMS {\n");
  printf("obj->base: 0x%lx\n", obj->base);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->gpuUuid:\n");
  printer_struct_nv_uuid(&(obj->gpuUuid));
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_TOOLS_WRITE_PROCESS_MEMORY_PARAMS(
    UVM_TOOLS_WRITE_PROCESS_MEMORY_PARAMS *obj) {
  printf("UVM_TOOLS_WRITE_PROCESS_MEMORY_PARAMS {\n");
  printf("obj->buffer: 0x%lx\n", obj->buffer);
  printf("obj->size: 0x%lx\n", obj->size);
  printf("obj->targetVa: 0x%lx\n", obj->targetVa);
  printf("obj->bytesWritten: 0x%lx\n", obj->bytesWritten);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_ENABLE_SYSTEM_WIDE_ATOMICS_PARAMS(
    UVM_ENABLE_SYSTEM_WIDE_ATOMICS_PARAMS *obj) {
  printf("UVM_ENABLE_SYSTEM_WIDE_ATOMICS_PARAMS {\n");
  printf("obj->gpu_uuid:\n");
  printer_struct_nv_uuid(&(obj->gpu_uuid));
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_MIGRATE_PARAMS(UVM_MIGRATE_PARAMS *obj) {
  printf("UVM_MIGRATE_PARAMS {\n");
  printf("obj->base: 0x%lx\n", obj->base);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->destinationUuid:\n");
  printer_struct_nv_uuid(&(obj->destinationUuid));
  printf("obj->flags: 0x%lx\n", obj->flags);
  printf("obj->semaphoreAddress: 0x%lx\n", obj->semaphoreAddress);
  printf("obj->semaphorePayload: 0x%lx\n", obj->semaphorePayload);
  printf("obj->cpuNumaNode: 0x%lx\n", obj->cpuNumaNode);
  printf("obj->userSpaceStart: 0x%lx\n", obj->userSpaceStart);
  printf("obj->userSpaceLength: 0x%lx\n", obj->userSpaceLength);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_ENABLE_PEER_ACCESS_PARAMS(UVM_ENABLE_PEER_ACCESS_PARAMS *obj) {
  printf("UVM_ENABLE_PEER_ACCESS_PARAMS {\n");
  printf("obj->gpuUuidA:\n");
  printer_struct_nv_uuid(&(obj->gpuUuidA));
  printf("obj->gpuUuidB:\n");
  printer_struct_nv_uuid(&(obj->gpuUuidB));
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_CREATE_EXTERNAL_RANGE_PARAMS(
    UVM_CREATE_EXTERNAL_RANGE_PARAMS *obj) {
  printf("UVM_CREATE_EXTERNAL_RANGE_PARAMS {\n");
  printf("obj->base: 0x%lx\n", obj->base);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_DESTROY_RANGE_GROUP_PARAMS(UVM_DESTROY_RANGE_GROUP_PARAMS *obj) {
  printf("UVM_DESTROY_RANGE_GROUP_PARAMS {\n");
  printf("obj->rangeGroupId: 0x%lx\n", obj->rangeGroupId);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_DISABLE_SYSTEM_WIDE_ATOMICS_PARAMS(
    UVM_DISABLE_SYSTEM_WIDE_ATOMICS_PARAMS *obj) {
  printf("UVM_DISABLE_SYSTEM_WIDE_ATOMICS_PARAMS {\n");
  printf("obj->gpu_uuid:\n");
  printer_struct_nv_uuid(&(obj->gpu_uuid));
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_MAP_EXTERNAL_ALLOCATION_PARAMS(
    UVM_MAP_EXTERNAL_ALLOCATION_PARAMS *obj) {
  printf("UVM_MAP_EXTERNAL_ALLOCATION_PARAMS {\n");
  printf("obj->base: 0x%lx\n", obj->base);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->offset: 0x%lx\n", obj->offset);
  for (uint64_t i = 0; i < 1; ++i) {
    printf("obj->perGpuAttributes[i]:\n");
    printer_UvmGpuMappingAttributes(&(obj->perGpuAttributes[i]));
  }
  printf("obj->gpuAttributesCount: 0x%lx\n", obj->gpuAttributesCount);
  printf("obj->rmCtrlFd: 0x%lx\n", obj->rmCtrlFd);
  printf("obj->hClient: 0x%lx\n", obj->hClient);
  printf("obj->hMemory: 0x%lx\n", obj->hMemory);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_FREE_PARAMS(UVM_FREE_PARAMS *obj) {
  printf("UVM_FREE_PARAMS {\n");
  printf("obj->base: 0x%lx\n", obj->base);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_PAGEABLE_MEM_ACCESS_ON_GPU_PARAMS(
    UVM_PAGEABLE_MEM_ACCESS_ON_GPU_PARAMS *obj) {
  printf("UVM_PAGEABLE_MEM_ACCESS_ON_GPU_PARAMS {\n");
  printf("obj->gpu_uuid:\n");
  printer_struct_nv_uuid(&(obj->gpu_uuid));
  printf("obj->pageableMemAccess: 0x%lx\n", obj->pageableMemAccess);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_UNREGISTER_GPU_PARAMS(UVM_UNREGISTER_GPU_PARAMS *obj) {
  printf("UVM_UNREGISTER_GPU_PARAMS {\n");
  printf("obj->gpu_uuid:\n");
  printer_struct_nv_uuid(&(obj->gpu_uuid));
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_TOOLS_READ_PROCESS_MEMORY_PARAMS(
    UVM_TOOLS_READ_PROCESS_MEMORY_PARAMS *obj) {
  printf("UVM_TOOLS_READ_PROCESS_MEMORY_PARAMS {\n");
  printf("obj->buffer: 0x%lx\n", obj->buffer);
  printf("obj->size: 0x%lx\n", obj->size);
  printf("obj->targetVa: 0x%lx\n", obj->targetVa);
  printf("obj->bytesRead: 0x%lx\n", obj->bytesRead);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_SET_ACCESSED_BY_PARAMS(UVM_SET_ACCESSED_BY_PARAMS *obj) {
  printf("UVM_SET_ACCESSED_BY_PARAMS {\n");
  printf("obj->requestedBase: 0x%lx\n", obj->requestedBase);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->accessedByUuid:\n");
  printer_struct_nv_uuid(&(obj->accessedByUuid));
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_TOOLS_GET_PROCESSOR_UUID_TABLE_PARAMS(
    UVM_TOOLS_GET_PROCESSOR_UUID_TABLE_PARAMS *obj) {
  printf("UVM_TOOLS_GET_PROCESSOR_UUID_TABLE_PARAMS {\n");
  printf("obj->tablePtr: 0x%lx\n", obj->tablePtr);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_PAGEABLE_MEM_ACCESS_PARAMS(UVM_PAGEABLE_MEM_ACCESS_PARAMS *obj) {
  printf("UVM_PAGEABLE_MEM_ACCESS_PARAMS {\n");
  printf("obj->pageableMemAccess: 0x%lx\n", obj->pageableMemAccess);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_CREATE_RANGE_GROUP_PARAMS(UVM_CREATE_RANGE_GROUP_PARAMS *obj) {
  printf("UVM_CREATE_RANGE_GROUP_PARAMS {\n");
  printf("obj->rangeGroupId: 0x%lx\n", obj->rangeGroupId);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_REGISTER_CHANNEL_PARAMS(UVM_REGISTER_CHANNEL_PARAMS *obj) {
  printf("UVM_REGISTER_CHANNEL_PARAMS {\n");
  printf("obj->gpuUuid:\n");
  printer_struct_nv_uuid(&(obj->gpuUuid));
  printf("obj->rmCtrlFd: 0x%lx\n", obj->rmCtrlFd);
  printf("obj->hClient: 0x%lx\n", obj->hClient);
  printf("obj->hChannel: 0x%lx\n", obj->hChannel);
  printf("obj->base: 0x%lx\n", obj->base);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_INITIALIZE_PARAMS(UVM_INITIALIZE_PARAMS *obj) {
  printf("UVM_INITIALIZE_PARAMS {\n");
  printf("obj->flags: 0x%lx\n", obj->flags);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_CLEAR_ALL_ACCESS_COUNTERS_PARAMS(
    UVM_CLEAR_ALL_ACCESS_COUNTERS_PARAMS *obj) {
  printf("UVM_CLEAR_ALL_ACCESS_COUNTERS_PARAMS {\n");
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_ALLOC_DEVICE_P2P_PARAMS(UVM_ALLOC_DEVICE_P2P_PARAMS *obj) {
  printf("UVM_ALLOC_DEVICE_P2P_PARAMS {\n");
  printf("obj->base: 0x%lx\n", obj->base);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->offset: 0x%lx\n", obj->offset);
  printf("obj->gpuUuid:\n");
  printer_struct_nv_uuid(&(obj->gpuUuid));
  printf("obj->rmCtrlFd: 0x%lx\n", obj->rmCtrlFd);
  printf("obj->hClient: 0x%lx\n", obj->hClient);
  printf("obj->hMemory: 0x%lx\n", obj->hMemory);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_SET_RANGE_GROUP_PARAMS(UVM_SET_RANGE_GROUP_PARAMS *obj) {
  printf("UVM_SET_RANGE_GROUP_PARAMS {\n");
  printf("obj->rangeGroupId: 0x%lx\n", obj->rangeGroupId);
  printf("obj->requestedBase: 0x%lx\n", obj->requestedBase);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_MM_INITIALIZE_PARAMS(UVM_MM_INITIALIZE_PARAMS *obj) {
  printf("UVM_MM_INITIALIZE_PARAMS {\n");
  printf("obj->uvmFd: 0x%lx\n", obj->uvmFd);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_MAP_EXTERNAL_SPARSE_PARAMS(UVM_MAP_EXTERNAL_SPARSE_PARAMS *obj) {
  printf("UVM_MAP_EXTERNAL_SPARSE_PARAMS {\n");
  printf("obj->base: 0x%lx\n", obj->base);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->gpuUuid:\n");
  printer_struct_nv_uuid(&(obj->gpuUuid));
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_VALIDATE_VA_RANGE_PARAMS(UVM_VALIDATE_VA_RANGE_PARAMS *obj) {
  printf("UVM_VALIDATE_VA_RANGE_PARAMS {\n");
  printf("obj->base: 0x%lx\n", obj->base);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_REGISTER_GPU_PARAMS(UVM_REGISTER_GPU_PARAMS *obj) {
  printf("UVM_REGISTER_GPU_PARAMS {\n");
  printf("obj->gpu_uuid:\n");
  printer_struct_nv_uuid(&(obj->gpu_uuid));
  printf("obj->numaEnabled: 0x%lx\n", obj->numaEnabled);
  printf("obj->numaNodeId: 0x%lx\n", obj->numaNodeId);
  printf("obj->rmCtrlFd: 0x%lx\n", obj->rmCtrlFd);
  printf("obj->hClient: 0x%lx\n", obj->hClient);
  printf("obj->hSmcPartRef: 0x%lx\n", obj->hSmcPartRef);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_PREVENT_MIGRATION_RANGE_GROUPS_PARAMS(
    UVM_PREVENT_MIGRATION_RANGE_GROUPS_PARAMS *obj) {
  printf("UVM_PREVENT_MIGRATION_RANGE_GROUPS_PARAMS {\n");
  for (uint64_t i = 0; i < 1; ++i) {
    printf("obj->rangeGroupIds[i]: 0x%lx\n", obj->rangeGroupIds[i]);
  }
  printf("obj->numGroupIds: 0x%lx\n", obj->numGroupIds);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_ALLOW_MIGRATION_RANGE_GROUPS_PARAMS(
    UVM_ALLOW_MIGRATION_RANGE_GROUPS_PARAMS *obj) {
  printf("UVM_ALLOW_MIGRATION_RANGE_GROUPS_PARAMS {\n");
  for (uint64_t i = 0; i < 1; ++i) {
    printf("obj->rangeGroupIds[i]: 0x%lx\n", obj->rangeGroupIds[i]);
  }
  printf("obj->numGroupIds: 0x%lx\n", obj->numGroupIds);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_DISABLE_PEER_ACCESS_PARAMS(UVM_DISABLE_PEER_ACCESS_PARAMS *obj) {
  printf("UVM_DISABLE_PEER_ACCESS_PARAMS {\n");
  printf("obj->gpuUuidA:\n");
  printer_struct_nv_uuid(&(obj->gpuUuidA));
  printf("obj->gpuUuidB:\n");
  printer_struct_nv_uuid(&(obj->gpuUuidB));
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_UNREGISTER_GPU_VASPACE_PARAMS(
    UVM_UNREGISTER_GPU_VASPACE_PARAMS *obj) {
  printf("UVM_UNREGISTER_GPU_VASPACE_PARAMS {\n");
  printf("obj->gpuUuid:\n");
  printer_struct_nv_uuid(&(obj->gpuUuid));
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_SET_PREFERRED_LOCATION_PARAMS(
    UVM_SET_PREFERRED_LOCATION_PARAMS *obj) {
  printf("UVM_SET_PREFERRED_LOCATION_PARAMS {\n");
  printf("obj->requestedBase: 0x%lx\n", obj->requestedBase);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->preferredLocation:\n");
  printer_struct_nv_uuid(&(obj->preferredLocation));
  printf("obj->preferredCpuNumaNode: 0x%lx\n", obj->preferredCpuNumaNode);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_UNSET_PREFERRED_LOCATION_PARAMS(
    UVM_UNSET_PREFERRED_LOCATION_PARAMS *obj) {
  printf("UVM_UNSET_PREFERRED_LOCATION_PARAMS {\n");
  printf("obj->requestedBase: 0x%lx\n", obj->requestedBase);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_UNSET_ACCESSED_BY_PARAMS(UVM_UNSET_ACCESSED_BY_PARAMS *obj) {
  printf("UVM_UNSET_ACCESSED_BY_PARAMS {\n");
  printf("obj->requestedBase: 0x%lx\n", obj->requestedBase);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->accessedByUuid:\n");
  printer_struct_nv_uuid(&(obj->accessedByUuid));
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_UNREGISTER_CHANNEL_PARAMS(UVM_UNREGISTER_CHANNEL_PARAMS *obj) {
  printf("UVM_UNREGISTER_CHANNEL_PARAMS {\n");
  printf("obj->gpuUuid:\n");
  printer_struct_nv_uuid(&(obj->gpuUuid));
  printf("obj->hClient: 0x%lx\n", obj->hClient);
  printf("obj->hChannel: 0x%lx\n", obj->hChannel);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_REGISTER_GPU_VASPACE_PARAMS(UVM_REGISTER_GPU_VASPACE_PARAMS *obj) {
  printf("UVM_REGISTER_GPU_VASPACE_PARAMS {\n");
  printf("obj->gpuUuid:\n");
  printer_struct_nv_uuid(&(obj->gpuUuid));
  printf("obj->rmCtrlFd: 0x%lx\n", obj->rmCtrlFd);
  printf("obj->hClient: 0x%lx\n", obj->hClient);
  printf("obj->hVaSpace: 0x%lx\n", obj->hVaSpace);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_TOOLS_FLUSH_EVENTS_PARAMS(UVM_TOOLS_FLUSH_EVENTS_PARAMS *obj) {
  printf("UVM_TOOLS_FLUSH_EVENTS_PARAMS {\n");
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_DISABLE_READ_DUPLICATION_PARAMS(
    UVM_DISABLE_READ_DUPLICATION_PARAMS *obj) {
  printf("UVM_DISABLE_READ_DUPLICATION_PARAMS {\n");
  printf("obj->requestedBase: 0x%lx\n", obj->requestedBase);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void
printer_UVM_POPULATE_PAGEABLE_PARAMS(UVM_POPULATE_PAGEABLE_PARAMS *obj) {
  printf("UVM_POPULATE_PAGEABLE_PARAMS {\n");
  printf("obj->base: 0x%lx\n", obj->base);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->flags: 0x%lx\n", obj->flags);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printer_UVM_ENABLE_READ_DUPLICATION_PARAMS(
    UVM_ENABLE_READ_DUPLICATION_PARAMS *obj) {
  printf("UVM_ENABLE_READ_DUPLICATION_PARAMS {\n");
  printf("obj->requestedBase: 0x%lx\n", obj->requestedBase);
  printf("obj->length: 0x%lx\n", obj->length);
  printf("obj->rmStatus: 0x%lx\n", obj->rmStatus);
  printf("}\n");
}

static inline void printarg(int cmd, void *arg) {
  switch (cmd) {
  case 805306369:
    printer_UVM_INITIALIZE_PARAMS((UVM_INITIALIZE_PARAMS *)arg);
    break;
  case 75:
    printer_UVM_MM_INITIALIZE_PARAMS((UVM_MM_INITIALIZE_PARAMS *)arg);
    break;
  case 39:
    printer_UVM_PAGEABLE_MEM_ACCESS_PARAMS(
        (UVM_PAGEABLE_MEM_ACCESS_PARAMS *)arg);
    break;
  case 70:
    printer_UVM_PAGEABLE_MEM_ACCESS_ON_GPU_PARAMS(
        (UVM_PAGEABLE_MEM_ACCESS_ON_GPU_PARAMS *)arg);
    break;
  case 37:
    printer_UVM_REGISTER_GPU_PARAMS((UVM_REGISTER_GPU_PARAMS *)arg);
    break;
  case 38:
    printer_UVM_UNREGISTER_GPU_PARAMS((UVM_UNREGISTER_GPU_PARAMS *)arg);
    break;
  case 23:
    printer_UVM_CREATE_RANGE_GROUP_PARAMS((UVM_CREATE_RANGE_GROUP_PARAMS *)arg);
    break;
  case 24:
    printer_UVM_DESTROY_RANGE_GROUP_PARAMS(
        (UVM_DESTROY_RANGE_GROUP_PARAMS *)arg);
    break;
  case 29:
    printer_UVM_ENABLE_PEER_ACCESS_PARAMS((UVM_ENABLE_PEER_ACCESS_PARAMS *)arg);
    break;
  case 30:
    printer_UVM_DISABLE_PEER_ACCESS_PARAMS(
        (UVM_DISABLE_PEER_ACCESS_PARAMS *)arg);
    break;
  case 31:
    printer_UVM_SET_RANGE_GROUP_PARAMS((UVM_SET_RANGE_GROUP_PARAMS *)arg);
    break;
  case 73:
    printer_UVM_CREATE_EXTERNAL_RANGE_PARAMS(
        (UVM_CREATE_EXTERNAL_RANGE_PARAMS *)arg);
    break;
  case 33:
    printer_UVM_MAP_EXTERNAL_ALLOCATION_PARAMS(
        (UVM_MAP_EXTERNAL_ALLOCATION_PARAMS *)arg);
    break;
  case 74:
    printer_UVM_MAP_EXTERNAL_SPARSE_PARAMS(
        (UVM_MAP_EXTERNAL_SPARSE_PARAMS *)arg);
    break;
  case 34:
    printer_UVM_FREE_PARAMS((UVM_FREE_PARAMS *)arg);
    break;
  case 40:
    printer_UVM_PREVENT_MIGRATION_RANGE_GROUPS_PARAMS(
        (UVM_PREVENT_MIGRATION_RANGE_GROUPS_PARAMS *)arg);
    break;
  case 41:
    printer_UVM_ALLOW_MIGRATION_RANGE_GROUPS_PARAMS(
        (UVM_ALLOW_MIGRATION_RANGE_GROUPS_PARAMS *)arg);
    break;
  case 42:
    printer_UVM_SET_PREFERRED_LOCATION_PARAMS(
        (UVM_SET_PREFERRED_LOCATION_PARAMS *)arg);
    break;
  case 43:
    printer_UVM_UNSET_PREFERRED_LOCATION_PARAMS(
        (UVM_UNSET_PREFERRED_LOCATION_PARAMS *)arg);
    break;
  case 46:
    printer_UVM_SET_ACCESSED_BY_PARAMS((UVM_SET_ACCESSED_BY_PARAMS *)arg);
    break;
  case 47:
    printer_UVM_UNSET_ACCESSED_BY_PARAMS((UVM_UNSET_ACCESSED_BY_PARAMS *)arg);
    break;
  case 25:
    printer_UVM_REGISTER_GPU_VASPACE_PARAMS(
        (UVM_REGISTER_GPU_VASPACE_PARAMS *)arg);
    break;
  case 26:
    printer_UVM_UNREGISTER_GPU_VASPACE_PARAMS(
        (UVM_UNREGISTER_GPU_VASPACE_PARAMS *)arg);
    break;
  case 27:
    printer_UVM_REGISTER_CHANNEL_PARAMS((UVM_REGISTER_CHANNEL_PARAMS *)arg);
    break;
  case 28:
    printer_UVM_UNREGISTER_CHANNEL_PARAMS((UVM_UNREGISTER_CHANNEL_PARAMS *)arg);
    break;
  case 44:
    printer_UVM_ENABLE_READ_DUPLICATION_PARAMS(
        (UVM_ENABLE_READ_DUPLICATION_PARAMS *)arg);
    break;
  case 45:
    printer_UVM_DISABLE_READ_DUPLICATION_PARAMS(
        (UVM_DISABLE_READ_DUPLICATION_PARAMS *)arg);
    break;
  case 51:
    printer_UVM_MIGRATE_PARAMS((UVM_MIGRATE_PARAMS *)arg);
    break;
  case 54:
    printer_UVM_ENABLE_SYSTEM_WIDE_ATOMICS_PARAMS(
        (UVM_ENABLE_SYSTEM_WIDE_ATOMICS_PARAMS *)arg);
    break;
  case 55:
    printer_UVM_DISABLE_SYSTEM_WIDE_ATOMICS_PARAMS(
        (UVM_DISABLE_SYSTEM_WIDE_ATOMICS_PARAMS *)arg);
    break;
  case 62:
    printer_UVM_TOOLS_READ_PROCESS_MEMORY_PARAMS(
        (UVM_TOOLS_READ_PROCESS_MEMORY_PARAMS *)arg);
    break;
  case 63:
    printer_UVM_TOOLS_WRITE_PROCESS_MEMORY_PARAMS(
        (UVM_TOOLS_WRITE_PROCESS_MEMORY_PARAMS *)arg);
    break;
  case 64:
    printer_UVM_TOOLS_GET_PROCESSOR_UUID_TABLE_PARAMS(
        (UVM_TOOLS_GET_PROCESSOR_UUID_TABLE_PARAMS *)arg);
    break;
  case 65:
    printer_UVM_MAP_DYNAMIC_PARALLELISM_REGION_PARAMS(
        (UVM_MAP_DYNAMIC_PARALLELISM_REGION_PARAMS *)arg);
    break;
  case 66:
    printer_UVM_UNMAP_EXTERNAL_PARAMS((UVM_UNMAP_EXTERNAL_PARAMS *)arg);
    break;
  case 53:
    printer_UVM_MIGRATE_RANGE_GROUP_PARAMS(
        (UVM_MIGRATE_RANGE_GROUP_PARAMS *)arg);
    break;
  case 67:
    printer_UVM_TOOLS_FLUSH_EVENTS_PARAMS((UVM_TOOLS_FLUSH_EVENTS_PARAMS *)arg);
    break;
  case 68:
    printer_UVM_ALLOC_SEMAPHORE_POOL_PARAMS(
        (UVM_ALLOC_SEMAPHORE_POOL_PARAMS *)arg);
    break;
  case 69:
    printer_UVM_CLEAN_UP_ZOMBIE_RESOURCES_PARAMS(
        (UVM_CLEAN_UP_ZOMBIE_RESOURCES_PARAMS *)arg);
    break;
  case 71:
    printer_UVM_POPULATE_PAGEABLE_PARAMS((UVM_POPULATE_PAGEABLE_PARAMS *)arg);
    break;
  case 72:
    printer_UVM_VALIDATE_VA_RANGE_PARAMS((UVM_VALIDATE_VA_RANGE_PARAMS *)arg);
    break;
  case 77:
    printer_UVM_TOOLS_GET_PROCESSOR_UUID_TABLE_PARAMS(
        (UVM_TOOLS_GET_PROCESSOR_UUID_TABLE_PARAMS *)arg);
    break;
  case 78:
    printer_UVM_ALLOC_DEVICE_P2P_PARAMS((UVM_ALLOC_DEVICE_P2P_PARAMS *)arg);
    break;
  case 79:
    printer_UVM_CLEAR_ALL_ACCESS_COUNTERS_PARAMS(
        (UVM_CLEAR_ALL_ACCESS_COUNTERS_PARAMS *)arg);
    break;
  case 111:
    printer_UVM_DUMP_GPU_MEMORY_PARAMS((UVM_DUMP_GPU_MEMORY_PARAMS *)arg);
    break;
  default:
    printf("Unknown cmd: %d\n", cmd);
    break;
  }
}
