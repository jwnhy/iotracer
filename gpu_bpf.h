#include "gpu_ioctl.h"
static inline uint64_t sizeofarg(uint64_t cmd, uint64_t arg) {
  switch(cmd) {
    case KBASE_IOCTL_SET_FLAGS:
      return sizeof(struct kbase_ioctl_set_flags);
      break;
    case KBASE_IOCTL_GET_GPUPROPS:
      return sizeof(struct kbase_ioctl_get_gpuprops);
      break;
    case KBASE_IOCTL_MEM_ALLOC:
      return sizeof(union kbase_ioctl_mem_alloc);
      break;
    case KBASE_IOCTL_MEM_QUERY:
      return sizeof(union kbase_ioctl_mem_query);
      break;
    case KBASE_IOCTL_MEM_FREE:
      return sizeof(struct kbase_ioctl_mem_free);
      break;
    case KBASE_IOCTL_HWCNT_READER_SETUP:
      return sizeof(struct kbase_ioctl_hwcnt_reader_setup);
      break;
    case KBASE_IOCTL_HWCNT_SET:
      return sizeof(struct kbase_ioctl_hwcnt_values);
      break;
    case KBASE_IOCTL_DISJOINT_QUERY:
      return sizeof(struct kbase_ioctl_disjoint_query);
      break;
    case KBASE_IOCTL_GET_DDK_VERSION:
      return sizeof(struct kbase_ioctl_get_ddk_version);
      break;
    case KBASE_IOCTL_MEM_JIT_INIT:
      return sizeof(struct kbase_ioctl_mem_jit_init);
      break;
    case KBASE_IOCTL_MEM_SYNC:
      return sizeof(struct kbase_ioctl_mem_sync);
      break;
    case KBASE_IOCTL_MEM_FIND_CPU_OFFSET:
      return sizeof(union kbase_ioctl_mem_find_cpu_offset);
      break;
    case KBASE_IOCTL_GET_CONTEXT_ID:
      return sizeof(struct kbase_ioctl_get_context_id);
      break;
    case KBASE_IOCTL_TLSTREAM_ACQUIRE:
      return sizeof(struct kbase_ioctl_tlstream_acquire);
      break;
    case KBASE_IOCTL_TLSTREAM_FLUSH:
      break;
    case KBASE_IOCTL_MEM_COMMIT:
      return sizeof(struct kbase_ioctl_mem_commit);
      break;
    case KBASE_IOCTL_MEM_ALIAS:
      return sizeof(union kbase_ioctl_mem_alias);
      break;
    case KBASE_IOCTL_MEM_IMPORT:
      return sizeof(union kbase_ioctl_mem_import);
      break;
    case KBASE_IOCTL_MEM_FLAGS_CHANGE:
      return sizeof(struct kbase_ioctl_mem_flags_change);
      break;
    case KBASE_IOCTL_STREAM_CREATE:
      return sizeof(struct kbase_ioctl_stream_create);
      break;
    case KBASE_IOCTL_FENCE_VALIDATE:
      return sizeof(struct kbase_ioctl_fence_validate);
      break;
    case KBASE_IOCTL_MEM_PROFILE_ADD:
      return sizeof(struct kbase_ioctl_mem_profile_add);
      break;
    case KBASE_IOCTL_STICKY_RESOURCE_MAP:
      return sizeof(struct kbase_ioctl_sticky_resource_map);
      break;
    case KBASE_IOCTL_STICKY_RESOURCE_UNMAP:
      return sizeof(struct kbase_ioctl_sticky_resource_unmap);
      break;
    case KBASE_IOCTL_MEM_FIND_GPU_START_AND_OFFSET:
      return sizeof(union kbase_ioctl_mem_find_gpu_start_and_offset);
      break;
    case KBASE_IOCTL_CINSTR_GWT_START:
      break;
    case KBASE_IOCTL_CINSTR_GWT_STOP:
      break;
    case KBASE_IOCTL_CINSTR_GWT_DUMP:
      return sizeof(union kbase_ioctl_cinstr_gwt_dump);
      break;
    case KBASE_IOCTL_MEM_EXEC_INIT:
      return sizeof(struct kbase_ioctl_mem_exec_init);
      break;
    case KBASE_IOCTL_GET_CPU_GPU_TIMEINFO:
      return sizeof(union kbase_ioctl_get_cpu_gpu_timeinfo);
      break;
    case KBASE_IOCTL_CONTEXT_PRIORITY_CHECK:
      return sizeof(struct kbase_ioctl_context_priority_check);
      break;
    case KBASE_IOCTL_SET_LIMITED_CORE_COUNT:
      return sizeof(struct kbase_ioctl_set_limited_core_count);
      break;
    case KBASE_IOCTL_KINSTR_PRFCNT_ENUM_INFO:
      return sizeof(struct kbase_ioctl_kinstr_prfcnt_enum_info);
      break;
    case KBASE_IOCTL_KINSTR_PRFCNT_SETUP:
      return sizeof(union kbase_ioctl_kinstr_prfcnt_setup);
      break;
    case KBASE_IOCTL_CS_QUEUE_REGISTER:
      return sizeof(struct kbase_ioctl_cs_queue_register);
      break;
    case KBASE_IOCTL_CS_QUEUE_KICK:
      return sizeof(struct kbase_ioctl_cs_queue_kick);
      break;
    case KBASE_IOCTL_CS_QUEUE_BIND:
      return sizeof(union kbase_ioctl_cs_queue_bind);
      break;
    case KBASE_IOCTL_CS_QUEUE_REGISTER_EX:
      return sizeof(struct kbase_ioctl_cs_queue_register_ex);
      break;
    case KBASE_IOCTL_CS_QUEUE_TERMINATE:
      return sizeof(struct kbase_ioctl_cs_queue_terminate);
      break;
    case KBASE_IOCTL_CS_QUEUE_GROUP_CREATE_1_6:
      return sizeof(union kbase_ioctl_cs_queue_group_create_1_6);
      break;
    case KBASE_IOCTL_CS_QUEUE_GROUP_CREATE:
      return sizeof(union kbase_ioctl_cs_queue_group_create);
      break;
    case KBASE_IOCTL_CS_QUEUE_GROUP_TERMINATE:
      return sizeof(struct kbase_ioctl_cs_queue_group_term);
      break;
    case KBASE_IOCTL_CS_EVENT_SIGNAL:
      break;
    case KBASE_IOCTL_KCPU_QUEUE_CREATE:
      return sizeof(struct kbase_ioctl_kcpu_queue_new);
      break;
    case KBASE_IOCTL_KCPU_QUEUE_DELETE:
      return sizeof(struct kbase_ioctl_kcpu_queue_delete);
      break;
    case KBASE_IOCTL_KCPU_QUEUE_ENQUEUE:
      return sizeof(struct kbase_ioctl_kcpu_queue_enqueue);
      break;
    case KBASE_IOCTL_CS_TILER_HEAP_INIT:
      return sizeof(union kbase_ioctl_cs_tiler_heap_init);
      break;
    case KBASE_IOCTL_CS_TILER_HEAP_INIT_1_13:
      return sizeof(union kbase_ioctl_cs_tiler_heap_init_1_13);
      break;
    case KBASE_IOCTL_CS_TILER_HEAP_TERM:
      return sizeof(struct kbase_ioctl_cs_tiler_heap_term);
      break;
    case KBASE_IOCTL_CS_GET_GLB_IFACE:
      return sizeof(union kbase_ioctl_cs_get_glb_iface);
      break;
    case KBASE_IOCTL_CS_CPU_QUEUE_DUMP:
      return sizeof(struct kbase_ioctl_cs_cpu_queue_info);
      break;
    case KBASE_IOCTL_MEM_ALLOC_EX:
      return sizeof(union kbase_ioctl_mem_alloc_ex);
      break;
    case KBASE_IOCTL_READ_USER_PAGE:
      return sizeof(union kbase_ioctl_read_user_page);
      break;
    case KBASE_IOCTL_VERSION_CHECK:
      return sizeof(struct kbase_ioctl_version_check);
      break;
    case KBASE_IOCTL_JOB_SUBMIT:
      return sizeof(struct kbase_ioctl_job_submit);
      break;
    case KBASE_IOCTL_POST_TERM:
      break;
    case KBASE_IOCTL_SOFT_EVENT_UPDATE:
      return sizeof(struct kbase_ioctl_soft_event_update);
      break;
    case KBASE_IOCTL_KINSTR_JM_FD:
      return sizeof(union kbase_kinstr_jm_fd);
      break;
    case KBASE_IOCTL_VERSION_CHECK_RESERVED:
      return sizeof(struct kbase_ioctl_version_check);
      break;
  }
 return 0;
}
static inline uint64_t sizeofret(uint64_t cmd, uint64_t arg) {
  switch(cmd) {
    case KBASE_IOCTL_SET_FLAGS:
      return sizeof(struct kbase_ioctl_set_flags);
      break;
    case KBASE_IOCTL_GET_GPUPROPS:
      return sizeof(struct kbase_ioctl_get_gpuprops);
      break;
    case KBASE_IOCTL_MEM_ALLOC:
      return sizeof(union kbase_ioctl_mem_alloc);
      break;
    case KBASE_IOCTL_MEM_QUERY:
      return sizeof(union kbase_ioctl_mem_query);
      break;
    case KBASE_IOCTL_MEM_FREE:
      return sizeof(struct kbase_ioctl_mem_free);
      break;
    case KBASE_IOCTL_HWCNT_READER_SETUP:
      return sizeof(struct kbase_ioctl_hwcnt_reader_setup);
      break;
    case KBASE_IOCTL_HWCNT_SET:
      return sizeof(struct kbase_ioctl_hwcnt_values);
      break;
    case KBASE_IOCTL_DISJOINT_QUERY:
      return sizeof(struct kbase_ioctl_disjoint_query);
      break;
    case KBASE_IOCTL_GET_DDK_VERSION:
      return sizeof(struct kbase_ioctl_get_ddk_version);
      break;
    case KBASE_IOCTL_MEM_JIT_INIT:
      return sizeof(struct kbase_ioctl_mem_jit_init);
      break;
    case KBASE_IOCTL_MEM_SYNC:
      return sizeof(struct kbase_ioctl_mem_sync);
      break;
    case KBASE_IOCTL_MEM_FIND_CPU_OFFSET:
      return sizeof(union kbase_ioctl_mem_find_cpu_offset);
      break;
    case KBASE_IOCTL_GET_CONTEXT_ID:
      return sizeof(struct kbase_ioctl_get_context_id);
      break;
    case KBASE_IOCTL_TLSTREAM_ACQUIRE:
      return sizeof(struct kbase_ioctl_tlstream_acquire);
      break;
    case KBASE_IOCTL_TLSTREAM_FLUSH:
      break;
    case KBASE_IOCTL_MEM_COMMIT:
      return sizeof(struct kbase_ioctl_mem_commit);
      break;
    case KBASE_IOCTL_MEM_ALIAS:
      return sizeof(union kbase_ioctl_mem_alias);
      break;
    case KBASE_IOCTL_MEM_IMPORT:
      return sizeof(union kbase_ioctl_mem_import);
      break;
    case KBASE_IOCTL_MEM_FLAGS_CHANGE:
      return sizeof(struct kbase_ioctl_mem_flags_change);
      break;
    case KBASE_IOCTL_STREAM_CREATE:
      return sizeof(struct kbase_ioctl_stream_create);
      break;
    case KBASE_IOCTL_FENCE_VALIDATE:
      return sizeof(struct kbase_ioctl_fence_validate);
      break;
    case KBASE_IOCTL_MEM_PROFILE_ADD:
      return sizeof(struct kbase_ioctl_mem_profile_add);
      break;
    case KBASE_IOCTL_STICKY_RESOURCE_MAP:
      return sizeof(struct kbase_ioctl_sticky_resource_map);
      break;
    case KBASE_IOCTL_STICKY_RESOURCE_UNMAP:
      return sizeof(struct kbase_ioctl_sticky_resource_unmap);
      break;
    case KBASE_IOCTL_MEM_FIND_GPU_START_AND_OFFSET:
      return sizeof(union kbase_ioctl_mem_find_gpu_start_and_offset);
      break;
    case KBASE_IOCTL_CINSTR_GWT_START:
      break;
    case KBASE_IOCTL_CINSTR_GWT_STOP:
      break;
    case KBASE_IOCTL_CINSTR_GWT_DUMP:
      return sizeof(union kbase_ioctl_cinstr_gwt_dump);
      break;
    case KBASE_IOCTL_MEM_EXEC_INIT:
      return sizeof(struct kbase_ioctl_mem_exec_init);
      break;
    case KBASE_IOCTL_GET_CPU_GPU_TIMEINFO:
      return sizeof(union kbase_ioctl_get_cpu_gpu_timeinfo);
      break;
    case KBASE_IOCTL_CONTEXT_PRIORITY_CHECK:
      return sizeof(struct kbase_ioctl_context_priority_check);
      break;
    case KBASE_IOCTL_SET_LIMITED_CORE_COUNT:
      return sizeof(struct kbase_ioctl_set_limited_core_count);
      break;
    case KBASE_IOCTL_KINSTR_PRFCNT_ENUM_INFO:
      return sizeof(struct kbase_ioctl_kinstr_prfcnt_enum_info);
      break;
    case KBASE_IOCTL_KINSTR_PRFCNT_SETUP:
      return sizeof(union kbase_ioctl_kinstr_prfcnt_setup);
      break;
    case KBASE_IOCTL_CS_QUEUE_REGISTER:
      return sizeof(struct kbase_ioctl_cs_queue_register);
      break;
    case KBASE_IOCTL_CS_QUEUE_KICK:
      return sizeof(struct kbase_ioctl_cs_queue_kick);
      break;
    case KBASE_IOCTL_CS_QUEUE_BIND:
      return sizeof(union kbase_ioctl_cs_queue_bind);
      break;
    case KBASE_IOCTL_CS_QUEUE_REGISTER_EX:
      return sizeof(struct kbase_ioctl_cs_queue_register_ex);
      break;
    case KBASE_IOCTL_CS_QUEUE_TERMINATE:
      return sizeof(struct kbase_ioctl_cs_queue_terminate);
      break;
    case KBASE_IOCTL_CS_QUEUE_GROUP_CREATE_1_6:
      return sizeof(union kbase_ioctl_cs_queue_group_create_1_6);
      break;
    case KBASE_IOCTL_CS_QUEUE_GROUP_CREATE:
      return sizeof(union kbase_ioctl_cs_queue_group_create);
      break;
    case KBASE_IOCTL_CS_QUEUE_GROUP_TERMINATE:
      return sizeof(struct kbase_ioctl_cs_queue_group_term);
      break;
    case KBASE_IOCTL_CS_EVENT_SIGNAL:
      break;
    case KBASE_IOCTL_KCPU_QUEUE_CREATE:
      return sizeof(struct kbase_ioctl_kcpu_queue_new);
      break;
    case KBASE_IOCTL_KCPU_QUEUE_DELETE:
      return sizeof(struct kbase_ioctl_kcpu_queue_delete);
      break;
    case KBASE_IOCTL_KCPU_QUEUE_ENQUEUE:
      return sizeof(struct kbase_ioctl_kcpu_queue_enqueue);
      break;
    case KBASE_IOCTL_CS_TILER_HEAP_INIT:
      return sizeof(union kbase_ioctl_cs_tiler_heap_init);
      break;
    case KBASE_IOCTL_CS_TILER_HEAP_INIT_1_13:
      return sizeof(union kbase_ioctl_cs_tiler_heap_init_1_13);
      break;
    case KBASE_IOCTL_CS_TILER_HEAP_TERM:
      return sizeof(struct kbase_ioctl_cs_tiler_heap_term);
      break;
    case KBASE_IOCTL_CS_GET_GLB_IFACE:
      return sizeof(union kbase_ioctl_cs_get_glb_iface);
      break;
    case KBASE_IOCTL_CS_CPU_QUEUE_DUMP:
      return sizeof(struct kbase_ioctl_cs_cpu_queue_info);
      break;
    case KBASE_IOCTL_MEM_ALLOC_EX:
      return sizeof(union kbase_ioctl_mem_alloc_ex);
      break;
    case KBASE_IOCTL_READ_USER_PAGE:
      return sizeof(union kbase_ioctl_read_user_page);
      break;
    case KBASE_IOCTL_VERSION_CHECK:
      return sizeof(struct kbase_ioctl_version_check);
      break;
    case KBASE_IOCTL_JOB_SUBMIT:
      return sizeof(struct kbase_ioctl_job_submit);
      break;
    case KBASE_IOCTL_POST_TERM:
      break;
    case KBASE_IOCTL_SOFT_EVENT_UPDATE:
      return sizeof(struct kbase_ioctl_soft_event_update);
      break;
    case KBASE_IOCTL_KINSTR_JM_FD:
      return sizeof(union kbase_kinstr_jm_fd);
      break;
    case KBASE_IOCTL_VERSION_CHECK_RESERVED:
      return sizeof(struct kbase_ioctl_version_check);
      break;
  }
 return 0;
}
