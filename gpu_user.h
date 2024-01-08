#include "gpu_ioctl.h"
#include <stdio.h>
static inline int printer_kbase_ioctl_set_flags(struct kbase_ioctl_set_flags* arg) {
  printf("  create_flags: 0x%x\n", arg->create_flags);
  return 0;
}
static inline int printer_kbase_ioctl_get_gpuprops(struct kbase_ioctl_get_gpuprops* arg) {
  printf("  buffer: 0x%lx\n", arg->buffer);
  printf("  size: 0x%x\n", arg->size);
  printf("  flags: 0x%x\n", arg->flags);
  return 0;
}
static inline int printer_kbase_ioctl_mem_alloc_in(union kbase_ioctl_mem_alloc* arg) {
  printf("  va_pages: 0x%lx\n", arg->in.va_pages);
  printf("  commit_pages: 0x%lx\n", arg->in.commit_pages);
  printf("  extension: 0x%lx\n", arg->in.extension);
  printf("  flags: 0x%lx\n", arg->in.flags);
  return 0;
}
static inline int printer_kbase_ioctl_mem_alloc_out(union kbase_ioctl_mem_alloc* arg) {
  printf("  flags: 0x%lx\n", arg->out.flags);
  printf("  gpu_va: 0x%lx\n", arg->out.gpu_va);
  return 0;
}
static inline int printer_kbase_ioctl_mem_query_in(union kbase_ioctl_mem_query* arg) {
  printf("  gpu_addr: 0x%lx\n", arg->in.gpu_addr);
  printf("  query: 0x%lx\n", arg->in.query);
  return 0;
}
static inline int printer_kbase_ioctl_mem_query_out(union kbase_ioctl_mem_query* arg) {
  printf("  value: 0x%lx\n", arg->out.value);
  return 0;
}
static inline int printer_kbase_ioctl_mem_free(struct kbase_ioctl_mem_free* arg) {
  printf("  gpu_addr: 0x%lx\n", arg->gpu_addr);
  return 0;
}
static inline int printer_kbase_ioctl_hwcnt_reader_setup(struct kbase_ioctl_hwcnt_reader_setup* arg) {
  printf("  buffer_count: 0x%x\n", arg->buffer_count);
  printf("  fe_bm: 0x%x\n", arg->fe_bm);
  printf("  shader_bm: 0x%x\n", arg->shader_bm);
  printf("  tiler_bm: 0x%x\n", arg->tiler_bm);
  printf("  mmu_l2_bm: 0x%x\n", arg->mmu_l2_bm);
  return 0;
}
static inline int printer_kbase_ioctl_hwcnt_values(struct kbase_ioctl_hwcnt_values* arg) {
  printf("  data: 0x%lx\n", arg->data);
  printf("  size: 0x%x\n", arg->size);
  printf("  padding: 0x%x\n", arg->padding);
  return 0;
}
static inline int printer_kbase_ioctl_disjoint_query(struct kbase_ioctl_disjoint_query* arg) {
  printf("  counter: 0x%x\n", arg->counter);
  return 0;
}
static inline int printer_kbase_ioctl_get_ddk_version(struct kbase_ioctl_get_ddk_version* arg) {
  printf("  version_buffer: 0x%lx\n", arg->version_buffer);
  printf("  size: 0x%x\n", arg->size);
  printf("  padding: 0x%x\n", arg->padding);
  return 0;
}
static inline int printer_kbase_ioctl_mem_jit_init(struct kbase_ioctl_mem_jit_init* arg) {
  printf("  va_pages: 0x%lx\n", arg->va_pages);
  printf("  max_allocations: 0x%x\n", arg->max_allocations);
  printf("  trim_level: 0x%x\n", arg->trim_level);
  printf("  group_id: 0x%x\n", arg->group_id);
  printf("  phys_pages: 0x%lx\n", arg->phys_pages);
  return 0;
}
static inline int printer_kbase_ioctl_mem_sync(struct kbase_ioctl_mem_sync* arg) {
  printf("  handle: 0x%lx\n", arg->handle);
  printf("  user_addr: 0x%lx\n", arg->user_addr);
  printf("  size: 0x%lx\n", arg->size);
  printf("  type: 0x%x\n", arg->type);
  return 0;
}
static inline int printer_kbase_ioctl_mem_find_cpu_offset_in(union kbase_ioctl_mem_find_cpu_offset* arg) {
  printf("  gpu_addr: 0x%lx\n", arg->in.gpu_addr);
  printf("  cpu_addr: 0x%lx\n", arg->in.cpu_addr);
  printf("  size: 0x%lx\n", arg->in.size);
  return 0;
}
static inline int printer_kbase_ioctl_mem_find_cpu_offset_out(union kbase_ioctl_mem_find_cpu_offset* arg) {
  printf("  offset: 0x%lx\n", arg->out.offset);
  return 0;
}
static inline int printer_kbase_ioctl_get_context_id(struct kbase_ioctl_get_context_id* arg) {
  printf("  id: 0x%x\n", arg->id);
  return 0;
}
static inline int printer_kbase_ioctl_tlstream_acquire(struct kbase_ioctl_tlstream_acquire* arg) {
  printf("  flags: 0x%x\n", arg->flags);
  return 0;
}
static inline int printer_kbase_ioctl_mem_commit(struct kbase_ioctl_mem_commit* arg) {
  printf("  gpu_addr: 0x%lx\n", arg->gpu_addr);
  printf("  pages: 0x%lx\n", arg->pages);
  return 0;
}
static inline int printer_kbase_ioctl_mem_alias_in(union kbase_ioctl_mem_alias* arg) {
  printf("  flags: 0x%lx\n", arg->in.flags);
  printf("  stride: 0x%lx\n", arg->in.stride);
  printf("  nents: 0x%lx\n", arg->in.nents);
  printf("  aliasing_info: 0x%lx\n", arg->in.aliasing_info);
  return 0;
}
static inline int printer_kbase_ioctl_mem_alias_out(union kbase_ioctl_mem_alias* arg) {
  printf("  flags: 0x%lx\n", arg->out.flags);
  printf("  gpu_va: 0x%lx\n", arg->out.gpu_va);
  printf("  va_pages: 0x%lx\n", arg->out.va_pages);
  return 0;
}
static inline int printer_kbase_ioctl_mem_import_in(union kbase_ioctl_mem_import* arg) {
  printf("  flags: 0x%lx\n", arg->in.flags);
  printf("  phandle: 0x%lx\n", arg->in.phandle);
  printf("  type: 0x%x\n", arg->in.type);
  printf("  padding: 0x%x\n", arg->in.padding);
  return 0;
}
static inline int printer_kbase_ioctl_mem_import_out(union kbase_ioctl_mem_import* arg) {
  printf("  flags: 0x%lx\n", arg->out.flags);
  printf("  gpu_va: 0x%lx\n", arg->out.gpu_va);
  printf("  va_pages: 0x%lx\n", arg->out.va_pages);
  return 0;
}
static inline int printer_kbase_ioctl_mem_flags_change(struct kbase_ioctl_mem_flags_change* arg) {
  printf("  gpu_va: 0x%lx\n", arg->gpu_va);
  printf("  flags: 0x%lx\n", arg->flags);
  printf("  mask: 0x%lx\n", arg->mask);
  return 0;
}
static inline int printer_kbase_ioctl_stream_create(struct kbase_ioctl_stream_create* arg) {
  return 0;
}
static inline int printer_kbase_ioctl_fence_validate(struct kbase_ioctl_fence_validate* arg) {
  printf("  fd: 0x%lx\n", arg->fd);
  return 0;
}
static inline int printer_kbase_ioctl_mem_profile_add(struct kbase_ioctl_mem_profile_add* arg) {
  printf("  buffer: 0x%lx\n", arg->buffer);
  printf("  len: 0x%x\n", arg->len);
  printf("  padding: 0x%x\n", arg->padding);
  return 0;
}
static inline int printer_kbase_ioctl_sticky_resource_map(struct kbase_ioctl_sticky_resource_map* arg) {
  printf("  count: 0x%lx\n", arg->count);
  printf("  address: 0x%lx\n", arg->address);
  return 0;
}
static inline int printer_kbase_ioctl_sticky_resource_unmap(struct kbase_ioctl_sticky_resource_unmap* arg) {
  printf("  count: 0x%lx\n", arg->count);
  printf("  address: 0x%lx\n", arg->address);
  return 0;
}
static inline int printer_kbase_ioctl_mem_find_gpu_start_and_offset_in(union kbase_ioctl_mem_find_gpu_start_and_offset* arg) {
  printf("  gpu_addr: 0x%lx\n", arg->in.gpu_addr);
  printf("  size: 0x%lx\n", arg->in.size);
  return 0;
}
static inline int printer_kbase_ioctl_mem_find_gpu_start_and_offset_out(union kbase_ioctl_mem_find_gpu_start_and_offset* arg) {
  printf("  start: 0x%lx\n", arg->out.start);
  printf("  offset: 0x%lx\n", arg->out.offset);
  return 0;
}
static inline int printer_kbase_ioctl_cinstr_gwt_dump_in(union kbase_ioctl_cinstr_gwt_dump* arg) {
  printf("  addr_buffer: 0x%lx\n", arg->in.addr_buffer);
  printf("  size_buffer: 0x%lx\n", arg->in.size_buffer);
  printf("  len: 0x%x\n", arg->in.len);
  printf("  padding: 0x%x\n", arg->in.padding);
  return 0;
}
static inline int printer_kbase_ioctl_cinstr_gwt_dump_out(union kbase_ioctl_cinstr_gwt_dump* arg) {
  printf("  no_of_addr_collected: 0x%x\n", arg->out.no_of_addr_collected);
  printf("  more_data_available: 0x%x\n", arg->out.more_data_available);
  return 0;
}
static inline int printer_kbase_ioctl_mem_exec_init(struct kbase_ioctl_mem_exec_init* arg) {
  printf("  va_pages: 0x%lx\n", arg->va_pages);
  return 0;
}
static inline int printer_kbase_ioctl_get_cpu_gpu_timeinfo_in(union kbase_ioctl_get_cpu_gpu_timeinfo* arg) {
  printf("  request_flags: 0x%x\n", arg->in.request_flags);
  return 0;
}
static inline int printer_kbase_ioctl_get_cpu_gpu_timeinfo_out(union kbase_ioctl_get_cpu_gpu_timeinfo* arg) {
  printf("  sec: 0x%lx\n", arg->out.sec);
  printf("  nsec: 0x%x\n", arg->out.nsec);
  printf("  padding: 0x%x\n", arg->out.padding);
  printf("  timestamp: 0x%lx\n", arg->out.timestamp);
  printf("  cycle_counter: 0x%lx\n", arg->out.cycle_counter);
  return 0;
}
static inline int printer_kbase_ioctl_context_priority_check(struct kbase_ioctl_context_priority_check* arg) {
  printf("  priority: 0x%x\n", arg->priority);
  return 0;
}
static inline int printer_kbase_ioctl_set_limited_core_count(struct kbase_ioctl_set_limited_core_count* arg) {
  printf("  max_core_count: 0x%x\n", arg->max_core_count);
  return 0;
}
static inline int printer_kbase_ioctl_kinstr_prfcnt_enum_info(struct kbase_ioctl_kinstr_prfcnt_enum_info* arg) {
  printf("  info_item_size: 0x%x\n", arg->info_item_size);
  printf("  info_item_count: 0x%x\n", arg->info_item_count);
  printf("  info_list_ptr: 0x%lx\n", arg->info_list_ptr);
  return 0;
}
static inline int printer_kbase_ioctl_kinstr_prfcnt_setup_in(union kbase_ioctl_kinstr_prfcnt_setup* arg) {
  printf("  request_item_count: 0x%x\n", arg->in.request_item_count);
  printf("  request_item_size: 0x%x\n", arg->in.request_item_size);
  printf("  requests_ptr: 0x%lx\n", arg->in.requests_ptr);
  return 0;
}
static inline int printer_kbase_ioctl_kinstr_prfcnt_setup_out(union kbase_ioctl_kinstr_prfcnt_setup* arg) {
  printf("  prfcnt_metadata_item_size: 0x%x\n", arg->out.prfcnt_metadata_item_size);
  printf("  prfcnt_mmap_size_bytes: 0x%x\n", arg->out.prfcnt_mmap_size_bytes);
  return 0;
}
static inline int printer_kbase_ioctl_cs_queue_register(struct kbase_ioctl_cs_queue_register* arg) {
  printf("  buffer_gpu_addr: 0x%lx\n", arg->buffer_gpu_addr);
  printf("  buffer_size: 0x%x\n", arg->buffer_size);
  printf("  priority: 0x%x\n", arg->priority);
  return 0;
}
static inline int printer_kbase_ioctl_cs_queue_kick(struct kbase_ioctl_cs_queue_kick* arg) {
  printf("  buffer_gpu_addr: 0x%lx\n", arg->buffer_gpu_addr);
  return 0;
}
static inline int printer_kbase_ioctl_cs_queue_bind_in(union kbase_ioctl_cs_queue_bind* arg) {
  printf("  buffer_gpu_addr: 0x%lx\n", arg->in.buffer_gpu_addr);
  printf("  group_handle: 0x%x\n", arg->in.group_handle);
  printf("  csi_index: 0x%x\n", arg->in.csi_index);
  return 0;
}
static inline int printer_kbase_ioctl_cs_queue_bind_out(union kbase_ioctl_cs_queue_bind* arg) {
  printf("  mmap_handle: 0x%lx\n", arg->out.mmap_handle);
  return 0;
}
static inline int printer_kbase_ioctl_cs_queue_register_ex(struct kbase_ioctl_cs_queue_register_ex* arg) {
  printf("  buffer_gpu_addr: 0x%lx\n", arg->buffer_gpu_addr);
  printf("  buffer_size: 0x%x\n", arg->buffer_size);
  printf("  priority: 0x%x\n", arg->priority);
  printf("  ex_offset_var_addr: 0x%lx\n", arg->ex_offset_var_addr);
  printf("  ex_buffer_base: 0x%lx\n", arg->ex_buffer_base);
  printf("  ex_buffer_size: 0x%x\n", arg->ex_buffer_size);
  printf("  ex_event_size: 0x%x\n", arg->ex_event_size);
  printf("  ex_event_state: 0x%x\n", arg->ex_event_state);
  return 0;
}
static inline int printer_kbase_ioctl_cs_queue_terminate(struct kbase_ioctl_cs_queue_terminate* arg) {
  printf("  buffer_gpu_addr: 0x%lx\n", arg->buffer_gpu_addr);
  return 0;
}
static inline int printer_kbase_ioctl_cs_queue_group_create_1_6_in(union kbase_ioctl_cs_queue_group_create_1_6* arg) {
  printf("  tiler_mask: 0x%lx\n", arg->in.tiler_mask);
  printf("  fragment_mask: 0x%lx\n", arg->in.fragment_mask);
  printf("  compute_mask: 0x%lx\n", arg->in.compute_mask);
  printf("  cs_min: 0x%x\n", arg->in.cs_min);
  printf("  priority: 0x%x\n", arg->in.priority);
  printf("  tiler_max: 0x%x\n", arg->in.tiler_max);
  printf("  fragment_max: 0x%x\n", arg->in.fragment_max);
  printf("  compute_max: 0x%x\n", arg->in.compute_max);
  return 0;
}
static inline int printer_kbase_ioctl_cs_queue_group_create_1_6_out(union kbase_ioctl_cs_queue_group_create_1_6* arg) {
  printf("  group_handle: 0x%x\n", arg->out.group_handle);
  printf("  group_uid: 0x%x\n", arg->out.group_uid);
  return 0;
}
static inline int printer_kbase_ioctl_cs_queue_group_create_in(union kbase_ioctl_cs_queue_group_create* arg) {
  printf("  tiler_mask: 0x%lx\n", arg->in.tiler_mask);
  printf("  fragment_mask: 0x%lx\n", arg->in.fragment_mask);
  printf("  compute_mask: 0x%lx\n", arg->in.compute_mask);
  printf("  cs_min: 0x%x\n", arg->in.cs_min);
  printf("  priority: 0x%x\n", arg->in.priority);
  printf("  tiler_max: 0x%x\n", arg->in.tiler_max);
  printf("  fragment_max: 0x%x\n", arg->in.fragment_max);
  printf("  compute_max: 0x%x\n", arg->in.compute_max);
  printf("  csi_handlers: 0x%x\n", arg->in.csi_handlers);
  printf("  dvs_buf: 0x%lx\n", arg->in.dvs_buf);
  return 0;
}
static inline int printer_kbase_ioctl_cs_queue_group_create_out(union kbase_ioctl_cs_queue_group_create* arg) {
  printf("  group_handle: 0x%x\n", arg->out.group_handle);
  printf("  group_uid: 0x%x\n", arg->out.group_uid);
  return 0;
}
static inline int printer_kbase_ioctl_cs_queue_group_term(struct kbase_ioctl_cs_queue_group_term* arg) {
  printf("  group_handle: 0x%x\n", arg->group_handle);
  return 0;
}
static inline int printer_kbase_ioctl_kcpu_queue_new(struct kbase_ioctl_kcpu_queue_new* arg) {
  printf("  id: 0x%x\n", arg->id);
  return 0;
}
static inline int printer_kbase_ioctl_kcpu_queue_delete(struct kbase_ioctl_kcpu_queue_delete* arg) {
  printf("  id: 0x%x\n", arg->id);
  return 0;
}
static inline int printer_kbase_ioctl_kcpu_queue_enqueue(struct kbase_ioctl_kcpu_queue_enqueue* arg) {
  printf("  addr: 0x%lx\n", arg->addr);
  printf("  nr_commands: 0x%x\n", arg->nr_commands);
  printf("  id: 0x%x\n", arg->id);
  return 0;
}
static inline int printer_kbase_ioctl_cs_tiler_heap_init_in(union kbase_ioctl_cs_tiler_heap_init* arg) {
  printf("  chunk_size: 0x%x\n", arg->in.chunk_size);
  printf("  initial_chunks: 0x%x\n", arg->in.initial_chunks);
  printf("  max_chunks: 0x%x\n", arg->in.max_chunks);
  printf("  target_in_flight: 0x%x\n", arg->in.target_in_flight);
  printf("  group_id: 0x%x\n", arg->in.group_id);
  printf("  padding: 0x%x\n", arg->in.padding);
  printf("  buf_desc_va: 0x%lx\n", arg->in.buf_desc_va);
  return 0;
}
static inline int printer_kbase_ioctl_cs_tiler_heap_init_out(union kbase_ioctl_cs_tiler_heap_init* arg) {
  printf("  gpu_heap_va: 0x%lx\n", arg->out.gpu_heap_va);
  printf("  first_chunk_va: 0x%lx\n", arg->out.first_chunk_va);
  return 0;
}
static inline int printer_kbase_ioctl_cs_tiler_heap_init_1_13_in(union kbase_ioctl_cs_tiler_heap_init_1_13* arg) {
  printf("  chunk_size: 0x%x\n", arg->in.chunk_size);
  printf("  initial_chunks: 0x%x\n", arg->in.initial_chunks);
  printf("  max_chunks: 0x%x\n", arg->in.max_chunks);
  printf("  target_in_flight: 0x%x\n", arg->in.target_in_flight);
  printf("  group_id: 0x%x\n", arg->in.group_id);
  printf("  padding: 0x%x\n", arg->in.padding);
  return 0;
}
static inline int printer_kbase_ioctl_cs_tiler_heap_init_1_13_out(union kbase_ioctl_cs_tiler_heap_init_1_13* arg) {
  printf("  gpu_heap_va: 0x%lx\n", arg->out.gpu_heap_va);
  printf("  first_chunk_va: 0x%lx\n", arg->out.first_chunk_va);
  return 0;
}
static inline int printer_kbase_ioctl_cs_tiler_heap_term(struct kbase_ioctl_cs_tiler_heap_term* arg) {
  printf("  gpu_heap_va: 0x%lx\n", arg->gpu_heap_va);
  return 0;
}
static inline int printer_kbase_ioctl_cs_get_glb_iface_in(union kbase_ioctl_cs_get_glb_iface* arg) {
  printf("  max_group_num: 0x%x\n", arg->in.max_group_num);
  printf("  max_total_stream_num: 0x%x\n", arg->in.max_total_stream_num);
  printf("  groups_ptr: 0x%lx\n", arg->in.groups_ptr);
  printf("  streams_ptr: 0x%lx\n", arg->in.streams_ptr);
  return 0;
}
static inline int printer_kbase_ioctl_cs_get_glb_iface_out(union kbase_ioctl_cs_get_glb_iface* arg) {
  printf("  glb_version: 0x%x\n", arg->out.glb_version);
  printf("  features: 0x%x\n", arg->out.features);
  printf("  group_num: 0x%x\n", arg->out.group_num);
  printf("  prfcnt_size: 0x%x\n", arg->out.prfcnt_size);
  printf("  total_stream_num: 0x%x\n", arg->out.total_stream_num);
  printf("  instr_features: 0x%x\n", arg->out.instr_features);
  return 0;
}
static inline int printer_kbase_ioctl_cs_cpu_queue_info(struct kbase_ioctl_cs_cpu_queue_info* arg) {
  printf("  buffer: 0x%lx\n", arg->buffer);
  printf("  size: 0x%lx\n", arg->size);
  return 0;
}
static inline int printer_kbase_ioctl_mem_alloc_ex_in(union kbase_ioctl_mem_alloc_ex* arg) {
  printf("  va_pages: 0x%lx\n", arg->in.va_pages);
  printf("  commit_pages: 0x%lx\n", arg->in.commit_pages);
  printf("  extension: 0x%lx\n", arg->in.extension);
  printf("  flags: 0x%lx\n", arg->in.flags);
  printf("  fixed_address: 0x%lx\n", arg->in.fixed_address);
  return 0;
}
static inline int printer_kbase_ioctl_mem_alloc_ex_out(union kbase_ioctl_mem_alloc_ex* arg) {
  printf("  flags: 0x%lx\n", arg->out.flags);
  printf("  gpu_va: 0x%lx\n", arg->out.gpu_va);
  return 0;
}
static inline int printer_kbase_ioctl_read_user_page_in(union kbase_ioctl_read_user_page* arg) {
  printf("  offset: 0x%x\n", arg->in.offset);
  printf("  padding: 0x%x\n", arg->in.padding);
  return 0;
}
static inline int printer_kbase_ioctl_read_user_page_out(union kbase_ioctl_read_user_page* arg) {
  printf("  val_lo: 0x%x\n", arg->out.val_lo);
  printf("  val_hi: 0x%x\n", arg->out.val_hi);
  return 0;
}
static inline int printer_kbase_ioctl_version_check(struct kbase_ioctl_version_check* arg) {
  printf("  major: 0x%x\n", arg->major);
  printf("  minor: 0x%x\n", arg->minor);
  return 0;
}
static inline int printer_kbase_ioctl_job_submit(struct kbase_ioctl_job_submit* arg) {
  printf("  addr: 0x%lx\n", arg->addr);
  printf("  nr_atoms: 0x%x\n", arg->nr_atoms);
  printf("  stride: 0x%x\n", arg->stride);
  return 0;
}
static inline int printer_kbase_ioctl_soft_event_update(struct kbase_ioctl_soft_event_update* arg) {
  printf("  event: 0x%lx\n", arg->event);
  printf("  new_status: 0x%x\n", arg->new_status);
  printf("  flags: 0x%x\n", arg->flags);
  return 0;
}
static inline int printer_kbase_kinstr_jm_fd_in(union kbase_kinstr_jm_fd* arg) {
  printf("  count: 0x%x\n", arg->in.count);
  return 0;
}
static inline int printer_kbase_kinstr_jm_fd_out(union kbase_kinstr_jm_fd* arg) {
  printf("  size: 0x%x\n", arg->out.size);
  printf("  version: 0x%x\n", arg->out.version);
  return 0;
}
static inline uint64_t cmdname(uint64_t cmd, uint64_t arg) {
  switch(cmd) {
    case KBASE_IOCTL_SET_FLAGS:
      return (uint64_t) "KBASE_IOCTL_SET_FLAGS";
      break;
    case KBASE_IOCTL_GET_GPUPROPS:
      return (uint64_t) "KBASE_IOCTL_GET_GPUPROPS";
      break;
    case KBASE_IOCTL_MEM_ALLOC:
      return (uint64_t) "KBASE_IOCTL_MEM_ALLOC";
      break;
    case KBASE_IOCTL_MEM_QUERY:
      return (uint64_t) "KBASE_IOCTL_MEM_QUERY";
      break;
    case KBASE_IOCTL_MEM_FREE:
      return (uint64_t) "KBASE_IOCTL_MEM_FREE";
      break;
    case KBASE_IOCTL_HWCNT_READER_SETUP:
      return (uint64_t) "KBASE_IOCTL_HWCNT_READER_SETUP";
      break;
    case KBASE_IOCTL_HWCNT_SET:
      return (uint64_t) "KBASE_IOCTL_HWCNT_SET";
      break;
    case KBASE_IOCTL_DISJOINT_QUERY:
      return (uint64_t) "KBASE_IOCTL_DISJOINT_QUERY";
      break;
    case KBASE_IOCTL_GET_DDK_VERSION:
      return (uint64_t) "KBASE_IOCTL_GET_DDK_VERSION";
      break;
    case KBASE_IOCTL_MEM_JIT_INIT:
      return (uint64_t) "KBASE_IOCTL_MEM_JIT_INIT";
      break;
    case KBASE_IOCTL_MEM_SYNC:
      return (uint64_t) "KBASE_IOCTL_MEM_SYNC";
      break;
    case KBASE_IOCTL_MEM_FIND_CPU_OFFSET:
      return (uint64_t) "KBASE_IOCTL_MEM_FIND_CPU_OFFSET";
      break;
    case KBASE_IOCTL_GET_CONTEXT_ID:
      return (uint64_t) "KBASE_IOCTL_GET_CONTEXT_ID";
      break;
    case KBASE_IOCTL_TLSTREAM_ACQUIRE:
      return (uint64_t) "KBASE_IOCTL_TLSTREAM_ACQUIRE";
      break;
    case KBASE_IOCTL_TLSTREAM_FLUSH:
      return (uint64_t) "KBASE_IOCTL_TLSTREAM_FLUSH";
      break;
    case KBASE_IOCTL_MEM_COMMIT:
      return (uint64_t) "KBASE_IOCTL_MEM_COMMIT";
      break;
    case KBASE_IOCTL_MEM_ALIAS:
      return (uint64_t) "KBASE_IOCTL_MEM_ALIAS";
      break;
    case KBASE_IOCTL_MEM_IMPORT:
      return (uint64_t) "KBASE_IOCTL_MEM_IMPORT";
      break;
    case KBASE_IOCTL_MEM_FLAGS_CHANGE:
      return (uint64_t) "KBASE_IOCTL_MEM_FLAGS_CHANGE";
      break;
    case KBASE_IOCTL_STREAM_CREATE:
      return (uint64_t) "KBASE_IOCTL_STREAM_CREATE";
      break;
    case KBASE_IOCTL_FENCE_VALIDATE:
      return (uint64_t) "KBASE_IOCTL_FENCE_VALIDATE";
      break;
    case KBASE_IOCTL_MEM_PROFILE_ADD:
      return (uint64_t) "KBASE_IOCTL_MEM_PROFILE_ADD";
      break;
    case KBASE_IOCTL_STICKY_RESOURCE_MAP:
      return (uint64_t) "KBASE_IOCTL_STICKY_RESOURCE_MAP";
      break;
    case KBASE_IOCTL_STICKY_RESOURCE_UNMAP:
      return (uint64_t) "KBASE_IOCTL_STICKY_RESOURCE_UNMAP";
      break;
    case KBASE_IOCTL_MEM_FIND_GPU_START_AND_OFFSET:
      return (uint64_t) "KBASE_IOCTL_MEM_FIND_GPU_START_AND_OFFSET";
      break;
    case KBASE_IOCTL_CINSTR_GWT_START:
      return (uint64_t) "KBASE_IOCTL_CINSTR_GWT_START";
      break;
    case KBASE_IOCTL_CINSTR_GWT_STOP:
      return (uint64_t) "KBASE_IOCTL_CINSTR_GWT_STOP";
      break;
    case KBASE_IOCTL_CINSTR_GWT_DUMP:
      return (uint64_t) "KBASE_IOCTL_CINSTR_GWT_DUMP";
      break;
    case KBASE_IOCTL_MEM_EXEC_INIT:
      return (uint64_t) "KBASE_IOCTL_MEM_EXEC_INIT";
      break;
    case KBASE_IOCTL_GET_CPU_GPU_TIMEINFO:
      return (uint64_t) "KBASE_IOCTL_GET_CPU_GPU_TIMEINFO";
      break;
    case KBASE_IOCTL_CONTEXT_PRIORITY_CHECK:
      return (uint64_t) "KBASE_IOCTL_CONTEXT_PRIORITY_CHECK";
      break;
    case KBASE_IOCTL_SET_LIMITED_CORE_COUNT:
      return (uint64_t) "KBASE_IOCTL_SET_LIMITED_CORE_COUNT";
      break;
    case KBASE_IOCTL_KINSTR_PRFCNT_ENUM_INFO:
      return (uint64_t) "KBASE_IOCTL_KINSTR_PRFCNT_ENUM_INFO";
      break;
    case KBASE_IOCTL_KINSTR_PRFCNT_SETUP:
      return (uint64_t) "KBASE_IOCTL_KINSTR_PRFCNT_SETUP";
      break;
    case KBASE_IOCTL_CS_QUEUE_REGISTER:
      return (uint64_t) "KBASE_IOCTL_CS_QUEUE_REGISTER";
      break;
    case KBASE_IOCTL_CS_QUEUE_KICK:
      return (uint64_t) "KBASE_IOCTL_CS_QUEUE_KICK";
      break;
    case KBASE_IOCTL_CS_QUEUE_BIND:
      return (uint64_t) "KBASE_IOCTL_CS_QUEUE_BIND";
      break;
    case KBASE_IOCTL_CS_QUEUE_REGISTER_EX:
      return (uint64_t) "KBASE_IOCTL_CS_QUEUE_REGISTER_EX";
      break;
    case KBASE_IOCTL_CS_QUEUE_TERMINATE:
      return (uint64_t) "KBASE_IOCTL_CS_QUEUE_TERMINATE";
      break;
    case KBASE_IOCTL_CS_QUEUE_GROUP_CREATE_1_6:
      return (uint64_t) "KBASE_IOCTL_CS_QUEUE_GROUP_CREATE_1_6";
      break;
    case KBASE_IOCTL_CS_QUEUE_GROUP_CREATE:
      return (uint64_t) "KBASE_IOCTL_CS_QUEUE_GROUP_CREATE";
      break;
    case KBASE_IOCTL_CS_QUEUE_GROUP_TERMINATE:
      return (uint64_t) "KBASE_IOCTL_CS_QUEUE_GROUP_TERMINATE";
      break;
    case KBASE_IOCTL_CS_EVENT_SIGNAL:
      return (uint64_t) "KBASE_IOCTL_CS_EVENT_SIGNAL";
      break;
    case KBASE_IOCTL_KCPU_QUEUE_CREATE:
      return (uint64_t) "KBASE_IOCTL_KCPU_QUEUE_CREATE";
      break;
    case KBASE_IOCTL_KCPU_QUEUE_DELETE:
      return (uint64_t) "KBASE_IOCTL_KCPU_QUEUE_DELETE";
      break;
    case KBASE_IOCTL_KCPU_QUEUE_ENQUEUE:
      return (uint64_t) "KBASE_IOCTL_KCPU_QUEUE_ENQUEUE";
      break;
    case KBASE_IOCTL_CS_TILER_HEAP_INIT:
      return (uint64_t) "KBASE_IOCTL_CS_TILER_HEAP_INIT";
      break;
    case KBASE_IOCTL_CS_TILER_HEAP_INIT_1_13:
      return (uint64_t) "KBASE_IOCTL_CS_TILER_HEAP_INIT_1_13";
      break;
    case KBASE_IOCTL_CS_TILER_HEAP_TERM:
      return (uint64_t) "KBASE_IOCTL_CS_TILER_HEAP_TERM";
      break;
    case KBASE_IOCTL_CS_GET_GLB_IFACE:
      return (uint64_t) "KBASE_IOCTL_CS_GET_GLB_IFACE";
      break;
    case KBASE_IOCTL_CS_CPU_QUEUE_DUMP:
      return (uint64_t) "KBASE_IOCTL_CS_CPU_QUEUE_DUMP";
      break;
    case KBASE_IOCTL_MEM_ALLOC_EX:
      return (uint64_t) "KBASE_IOCTL_MEM_ALLOC_EX";
      break;
    case KBASE_IOCTL_READ_USER_PAGE:
      return (uint64_t) "KBASE_IOCTL_READ_USER_PAGE";
      break;
    case KBASE_IOCTL_VERSION_CHECK:
      return (uint64_t) "KBASE_IOCTL_VERSION_CHECK";
      break;
    case KBASE_IOCTL_JOB_SUBMIT:
      return (uint64_t) "KBASE_IOCTL_JOB_SUBMIT";
      break;
    case KBASE_IOCTL_POST_TERM:
      return (uint64_t) "KBASE_IOCTL_POST_TERM";
      break;
    case KBASE_IOCTL_SOFT_EVENT_UPDATE:
      return (uint64_t) "KBASE_IOCTL_SOFT_EVENT_UPDATE";
      break;
    case KBASE_IOCTL_KINSTR_JM_FD:
      return (uint64_t) "KBASE_IOCTL_KINSTR_JM_FD";
      break;
    case KBASE_IOCTL_VERSION_CHECK_RESERVED:
      return (uint64_t) "KBASE_IOCTL_VERSION_CHECK_RESERVED";
      break;
  }
 return 0;
}
static inline uint64_t printerofarg(uint64_t cmd, uint64_t arg) {
  switch(cmd) {
    case KBASE_IOCTL_SET_FLAGS:
      printer_kbase_ioctl_set_flags((struct kbase_ioctl_set_flags *)arg);
      break;
    case KBASE_IOCTL_GET_GPUPROPS:
      printer_kbase_ioctl_get_gpuprops((struct kbase_ioctl_get_gpuprops *)arg);
      break;
    case KBASE_IOCTL_MEM_ALLOC:
      printer_kbase_ioctl_mem_alloc_in((union kbase_ioctl_mem_alloc *)arg);
      break;
    case KBASE_IOCTL_MEM_QUERY:
      printer_kbase_ioctl_mem_query_in((union kbase_ioctl_mem_query *)arg);
      break;
    case KBASE_IOCTL_MEM_FREE:
      printer_kbase_ioctl_mem_free((struct kbase_ioctl_mem_free *)arg);
      break;
    case KBASE_IOCTL_HWCNT_READER_SETUP:
      printer_kbase_ioctl_hwcnt_reader_setup((struct kbase_ioctl_hwcnt_reader_setup *)arg);
      break;
    case KBASE_IOCTL_HWCNT_SET:
      printer_kbase_ioctl_hwcnt_values((struct kbase_ioctl_hwcnt_values *)arg);
      break;
    case KBASE_IOCTL_DISJOINT_QUERY:
      printer_kbase_ioctl_disjoint_query((struct kbase_ioctl_disjoint_query *)arg);
      break;
    case KBASE_IOCTL_GET_DDK_VERSION:
      printer_kbase_ioctl_get_ddk_version((struct kbase_ioctl_get_ddk_version *)arg);
      break;
    case KBASE_IOCTL_MEM_JIT_INIT:
      printer_kbase_ioctl_mem_jit_init((struct kbase_ioctl_mem_jit_init *)arg);
      break;
    case KBASE_IOCTL_MEM_SYNC:
      printer_kbase_ioctl_mem_sync((struct kbase_ioctl_mem_sync *)arg);
      break;
    case KBASE_IOCTL_MEM_FIND_CPU_OFFSET:
      printer_kbase_ioctl_mem_find_cpu_offset_in((union kbase_ioctl_mem_find_cpu_offset *)arg);
      break;
    case KBASE_IOCTL_GET_CONTEXT_ID:
      printer_kbase_ioctl_get_context_id((struct kbase_ioctl_get_context_id *)arg);
      break;
    case KBASE_IOCTL_TLSTREAM_ACQUIRE:
      printer_kbase_ioctl_tlstream_acquire((struct kbase_ioctl_tlstream_acquire *)arg);
      break;
    case KBASE_IOCTL_TLSTREAM_FLUSH:
      break;
    case KBASE_IOCTL_MEM_COMMIT:
      printer_kbase_ioctl_mem_commit((struct kbase_ioctl_mem_commit *)arg);
      break;
    case KBASE_IOCTL_MEM_ALIAS:
      printer_kbase_ioctl_mem_alias_in((union kbase_ioctl_mem_alias *)arg);
      break;
    case KBASE_IOCTL_MEM_IMPORT:
      printer_kbase_ioctl_mem_import_in((union kbase_ioctl_mem_import *)arg);
      break;
    case KBASE_IOCTL_MEM_FLAGS_CHANGE:
      printer_kbase_ioctl_mem_flags_change((struct kbase_ioctl_mem_flags_change *)arg);
      break;
    case KBASE_IOCTL_STREAM_CREATE:
      printer_kbase_ioctl_stream_create((struct kbase_ioctl_stream_create *)arg);
      break;
    case KBASE_IOCTL_FENCE_VALIDATE:
      printer_kbase_ioctl_fence_validate((struct kbase_ioctl_fence_validate *)arg);
      break;
    case KBASE_IOCTL_MEM_PROFILE_ADD:
      printer_kbase_ioctl_mem_profile_add((struct kbase_ioctl_mem_profile_add *)arg);
      break;
    case KBASE_IOCTL_STICKY_RESOURCE_MAP:
      printer_kbase_ioctl_sticky_resource_map((struct kbase_ioctl_sticky_resource_map *)arg);
      break;
    case KBASE_IOCTL_STICKY_RESOURCE_UNMAP:
      printer_kbase_ioctl_sticky_resource_unmap((struct kbase_ioctl_sticky_resource_unmap *)arg);
      break;
    case KBASE_IOCTL_MEM_FIND_GPU_START_AND_OFFSET:
      printer_kbase_ioctl_mem_find_gpu_start_and_offset_in((union kbase_ioctl_mem_find_gpu_start_and_offset *)arg);
      break;
    case KBASE_IOCTL_CINSTR_GWT_START:
      break;
    case KBASE_IOCTL_CINSTR_GWT_STOP:
      break;
    case KBASE_IOCTL_CINSTR_GWT_DUMP:
      printer_kbase_ioctl_cinstr_gwt_dump_in((union kbase_ioctl_cinstr_gwt_dump *)arg);
      break;
    case KBASE_IOCTL_MEM_EXEC_INIT:
      printer_kbase_ioctl_mem_exec_init((struct kbase_ioctl_mem_exec_init *)arg);
      break;
    case KBASE_IOCTL_GET_CPU_GPU_TIMEINFO:
      printer_kbase_ioctl_get_cpu_gpu_timeinfo_in((union kbase_ioctl_get_cpu_gpu_timeinfo *)arg);
      break;
    case KBASE_IOCTL_CONTEXT_PRIORITY_CHECK:
      printer_kbase_ioctl_context_priority_check((struct kbase_ioctl_context_priority_check *)arg);
      break;
    case KBASE_IOCTL_SET_LIMITED_CORE_COUNT:
      printer_kbase_ioctl_set_limited_core_count((struct kbase_ioctl_set_limited_core_count *)arg);
      break;
    case KBASE_IOCTL_KINSTR_PRFCNT_ENUM_INFO:
      printer_kbase_ioctl_kinstr_prfcnt_enum_info((struct kbase_ioctl_kinstr_prfcnt_enum_info *)arg);
      break;
    case KBASE_IOCTL_KINSTR_PRFCNT_SETUP:
      printer_kbase_ioctl_kinstr_prfcnt_setup_in((union kbase_ioctl_kinstr_prfcnt_setup *)arg);
      break;
    case KBASE_IOCTL_CS_QUEUE_REGISTER:
      printer_kbase_ioctl_cs_queue_register((struct kbase_ioctl_cs_queue_register *)arg);
      break;
    case KBASE_IOCTL_CS_QUEUE_KICK:
      printer_kbase_ioctl_cs_queue_kick((struct kbase_ioctl_cs_queue_kick *)arg);
      break;
    case KBASE_IOCTL_CS_QUEUE_BIND:
      printer_kbase_ioctl_cs_queue_bind_in((union kbase_ioctl_cs_queue_bind *)arg);
      break;
    case KBASE_IOCTL_CS_QUEUE_REGISTER_EX:
      printer_kbase_ioctl_cs_queue_register_ex((struct kbase_ioctl_cs_queue_register_ex *)arg);
      break;
    case KBASE_IOCTL_CS_QUEUE_TERMINATE:
      printer_kbase_ioctl_cs_queue_terminate((struct kbase_ioctl_cs_queue_terminate *)arg);
      break;
    case KBASE_IOCTL_CS_QUEUE_GROUP_CREATE_1_6:
      printer_kbase_ioctl_cs_queue_group_create_1_6_in((union kbase_ioctl_cs_queue_group_create_1_6 *)arg);
      break;
    case KBASE_IOCTL_CS_QUEUE_GROUP_CREATE:
      printer_kbase_ioctl_cs_queue_group_create_in((union kbase_ioctl_cs_queue_group_create *)arg);
      break;
    case KBASE_IOCTL_CS_QUEUE_GROUP_TERMINATE:
      printer_kbase_ioctl_cs_queue_group_term((struct kbase_ioctl_cs_queue_group_term *)arg);
      break;
    case KBASE_IOCTL_CS_EVENT_SIGNAL:
      break;
    case KBASE_IOCTL_KCPU_QUEUE_CREATE:
      printer_kbase_ioctl_kcpu_queue_new((struct kbase_ioctl_kcpu_queue_new *)arg);
      break;
    case KBASE_IOCTL_KCPU_QUEUE_DELETE:
      printer_kbase_ioctl_kcpu_queue_delete((struct kbase_ioctl_kcpu_queue_delete *)arg);
      break;
    case KBASE_IOCTL_KCPU_QUEUE_ENQUEUE:
      printer_kbase_ioctl_kcpu_queue_enqueue((struct kbase_ioctl_kcpu_queue_enqueue *)arg);
      break;
    case KBASE_IOCTL_CS_TILER_HEAP_INIT:
      printer_kbase_ioctl_cs_tiler_heap_init_in((union kbase_ioctl_cs_tiler_heap_init *)arg);
      break;
    case KBASE_IOCTL_CS_TILER_HEAP_INIT_1_13:
      printer_kbase_ioctl_cs_tiler_heap_init_1_13_in((union kbase_ioctl_cs_tiler_heap_init_1_13 *)arg);
      break;
    case KBASE_IOCTL_CS_TILER_HEAP_TERM:
      printer_kbase_ioctl_cs_tiler_heap_term((struct kbase_ioctl_cs_tiler_heap_term *)arg);
      break;
    case KBASE_IOCTL_CS_GET_GLB_IFACE:
      printer_kbase_ioctl_cs_get_glb_iface_in((union kbase_ioctl_cs_get_glb_iface *)arg);
      break;
    case KBASE_IOCTL_CS_CPU_QUEUE_DUMP:
      printer_kbase_ioctl_cs_cpu_queue_info((struct kbase_ioctl_cs_cpu_queue_info *)arg);
      break;
    case KBASE_IOCTL_MEM_ALLOC_EX:
      printer_kbase_ioctl_mem_alloc_ex_in((union kbase_ioctl_mem_alloc_ex *)arg);
      break;
    case KBASE_IOCTL_READ_USER_PAGE:
      printer_kbase_ioctl_read_user_page_in((union kbase_ioctl_read_user_page *)arg);
      break;
    case KBASE_IOCTL_VERSION_CHECK:
      printer_kbase_ioctl_version_check((struct kbase_ioctl_version_check *)arg);
      break;
    case KBASE_IOCTL_JOB_SUBMIT:
      printer_kbase_ioctl_job_submit((struct kbase_ioctl_job_submit *)arg);
      break;
    case KBASE_IOCTL_POST_TERM:
      break;
    case KBASE_IOCTL_SOFT_EVENT_UPDATE:
      printer_kbase_ioctl_soft_event_update((struct kbase_ioctl_soft_event_update *)arg);
      break;
    case KBASE_IOCTL_KINSTR_JM_FD:
      printer_kbase_kinstr_jm_fd_in((union kbase_kinstr_jm_fd *)arg);
      break;
    case KBASE_IOCTL_VERSION_CHECK_RESERVED:
      printer_kbase_ioctl_version_check((struct kbase_ioctl_version_check *)arg);
      break;
  }
 return 0;
}
static inline uint64_t printerofret(uint64_t cmd, uint64_t arg) {
  switch(cmd) {
    case KBASE_IOCTL_SET_FLAGS:
      printer_kbase_ioctl_set_flags((struct kbase_ioctl_set_flags *)arg);
      break;
    case KBASE_IOCTL_GET_GPUPROPS:
      printer_kbase_ioctl_get_gpuprops((struct kbase_ioctl_get_gpuprops *)arg);
      break;
    case KBASE_IOCTL_MEM_ALLOC:
      printer_kbase_ioctl_mem_alloc_out((union kbase_ioctl_mem_alloc *)arg);
      break;
    case KBASE_IOCTL_MEM_QUERY:
      printer_kbase_ioctl_mem_query_out((union kbase_ioctl_mem_query *)arg);
      break;
    case KBASE_IOCTL_MEM_FREE:
      printer_kbase_ioctl_mem_free((struct kbase_ioctl_mem_free *)arg);
      break;
    case KBASE_IOCTL_HWCNT_READER_SETUP:
      printer_kbase_ioctl_hwcnt_reader_setup((struct kbase_ioctl_hwcnt_reader_setup *)arg);
      break;
    case KBASE_IOCTL_HWCNT_SET:
      printer_kbase_ioctl_hwcnt_values((struct kbase_ioctl_hwcnt_values *)arg);
      break;
    case KBASE_IOCTL_DISJOINT_QUERY:
      printer_kbase_ioctl_disjoint_query((struct kbase_ioctl_disjoint_query *)arg);
      break;
    case KBASE_IOCTL_GET_DDK_VERSION:
      printer_kbase_ioctl_get_ddk_version((struct kbase_ioctl_get_ddk_version *)arg);
      break;
    case KBASE_IOCTL_MEM_JIT_INIT:
      printer_kbase_ioctl_mem_jit_init((struct kbase_ioctl_mem_jit_init *)arg);
      break;
    case KBASE_IOCTL_MEM_SYNC:
      printer_kbase_ioctl_mem_sync((struct kbase_ioctl_mem_sync *)arg);
      break;
    case KBASE_IOCTL_MEM_FIND_CPU_OFFSET:
      printer_kbase_ioctl_mem_find_cpu_offset_out((union kbase_ioctl_mem_find_cpu_offset *)arg);
      break;
    case KBASE_IOCTL_GET_CONTEXT_ID:
      printer_kbase_ioctl_get_context_id((struct kbase_ioctl_get_context_id *)arg);
      break;
    case KBASE_IOCTL_TLSTREAM_ACQUIRE:
      printer_kbase_ioctl_tlstream_acquire((struct kbase_ioctl_tlstream_acquire *)arg);
      break;
    case KBASE_IOCTL_TLSTREAM_FLUSH:
      break;
    case KBASE_IOCTL_MEM_COMMIT:
      printer_kbase_ioctl_mem_commit((struct kbase_ioctl_mem_commit *)arg);
      break;
    case KBASE_IOCTL_MEM_ALIAS:
      printer_kbase_ioctl_mem_alias_out((union kbase_ioctl_mem_alias *)arg);
      break;
    case KBASE_IOCTL_MEM_IMPORT:
      printer_kbase_ioctl_mem_import_out((union kbase_ioctl_mem_import *)arg);
      break;
    case KBASE_IOCTL_MEM_FLAGS_CHANGE:
      printer_kbase_ioctl_mem_flags_change((struct kbase_ioctl_mem_flags_change *)arg);
      break;
    case KBASE_IOCTL_STREAM_CREATE:
      printer_kbase_ioctl_stream_create((struct kbase_ioctl_stream_create *)arg);
      break;
    case KBASE_IOCTL_FENCE_VALIDATE:
      printer_kbase_ioctl_fence_validate((struct kbase_ioctl_fence_validate *)arg);
      break;
    case KBASE_IOCTL_MEM_PROFILE_ADD:
      printer_kbase_ioctl_mem_profile_add((struct kbase_ioctl_mem_profile_add *)arg);
      break;
    case KBASE_IOCTL_STICKY_RESOURCE_MAP:
      printer_kbase_ioctl_sticky_resource_map((struct kbase_ioctl_sticky_resource_map *)arg);
      break;
    case KBASE_IOCTL_STICKY_RESOURCE_UNMAP:
      printer_kbase_ioctl_sticky_resource_unmap((struct kbase_ioctl_sticky_resource_unmap *)arg);
      break;
    case KBASE_IOCTL_MEM_FIND_GPU_START_AND_OFFSET:
      printer_kbase_ioctl_mem_find_gpu_start_and_offset_out((union kbase_ioctl_mem_find_gpu_start_and_offset *)arg);
      break;
    case KBASE_IOCTL_CINSTR_GWT_START:
      break;
    case KBASE_IOCTL_CINSTR_GWT_STOP:
      break;
    case KBASE_IOCTL_CINSTR_GWT_DUMP:
      printer_kbase_ioctl_cinstr_gwt_dump_out((union kbase_ioctl_cinstr_gwt_dump *)arg);
      break;
    case KBASE_IOCTL_MEM_EXEC_INIT:
      printer_kbase_ioctl_mem_exec_init((struct kbase_ioctl_mem_exec_init *)arg);
      break;
    case KBASE_IOCTL_GET_CPU_GPU_TIMEINFO:
      printer_kbase_ioctl_get_cpu_gpu_timeinfo_out((union kbase_ioctl_get_cpu_gpu_timeinfo *)arg);
      break;
    case KBASE_IOCTL_CONTEXT_PRIORITY_CHECK:
      printer_kbase_ioctl_context_priority_check((struct kbase_ioctl_context_priority_check *)arg);
      break;
    case KBASE_IOCTL_SET_LIMITED_CORE_COUNT:
      printer_kbase_ioctl_set_limited_core_count((struct kbase_ioctl_set_limited_core_count *)arg);
      break;
    case KBASE_IOCTL_KINSTR_PRFCNT_ENUM_INFO:
      printer_kbase_ioctl_kinstr_prfcnt_enum_info((struct kbase_ioctl_kinstr_prfcnt_enum_info *)arg);
      break;
    case KBASE_IOCTL_KINSTR_PRFCNT_SETUP:
      printer_kbase_ioctl_kinstr_prfcnt_setup_out((union kbase_ioctl_kinstr_prfcnt_setup *)arg);
      break;
    case KBASE_IOCTL_CS_QUEUE_REGISTER:
      printer_kbase_ioctl_cs_queue_register((struct kbase_ioctl_cs_queue_register *)arg);
      break;
    case KBASE_IOCTL_CS_QUEUE_KICK:
      printer_kbase_ioctl_cs_queue_kick((struct kbase_ioctl_cs_queue_kick *)arg);
      break;
    case KBASE_IOCTL_CS_QUEUE_BIND:
      printer_kbase_ioctl_cs_queue_bind_out((union kbase_ioctl_cs_queue_bind *)arg);
      break;
    case KBASE_IOCTL_CS_QUEUE_REGISTER_EX:
      printer_kbase_ioctl_cs_queue_register_ex((struct kbase_ioctl_cs_queue_register_ex *)arg);
      break;
    case KBASE_IOCTL_CS_QUEUE_TERMINATE:
      printer_kbase_ioctl_cs_queue_terminate((struct kbase_ioctl_cs_queue_terminate *)arg);
      break;
    case KBASE_IOCTL_CS_QUEUE_GROUP_CREATE_1_6:
      printer_kbase_ioctl_cs_queue_group_create_1_6_out((union kbase_ioctl_cs_queue_group_create_1_6 *)arg);
      break;
    case KBASE_IOCTL_CS_QUEUE_GROUP_CREATE:
      printer_kbase_ioctl_cs_queue_group_create_out((union kbase_ioctl_cs_queue_group_create *)arg);
      break;
    case KBASE_IOCTL_CS_QUEUE_GROUP_TERMINATE:
      printer_kbase_ioctl_cs_queue_group_term((struct kbase_ioctl_cs_queue_group_term *)arg);
      break;
    case KBASE_IOCTL_CS_EVENT_SIGNAL:
      break;
    case KBASE_IOCTL_KCPU_QUEUE_CREATE:
      printer_kbase_ioctl_kcpu_queue_new((struct kbase_ioctl_kcpu_queue_new *)arg);
      break;
    case KBASE_IOCTL_KCPU_QUEUE_DELETE:
      printer_kbase_ioctl_kcpu_queue_delete((struct kbase_ioctl_kcpu_queue_delete *)arg);
      break;
    case KBASE_IOCTL_KCPU_QUEUE_ENQUEUE:
      printer_kbase_ioctl_kcpu_queue_enqueue((struct kbase_ioctl_kcpu_queue_enqueue *)arg);
      break;
    case KBASE_IOCTL_CS_TILER_HEAP_INIT:
      printer_kbase_ioctl_cs_tiler_heap_init_out((union kbase_ioctl_cs_tiler_heap_init *)arg);
      break;
    case KBASE_IOCTL_CS_TILER_HEAP_INIT_1_13:
      printer_kbase_ioctl_cs_tiler_heap_init_1_13_out((union kbase_ioctl_cs_tiler_heap_init_1_13 *)arg);
      break;
    case KBASE_IOCTL_CS_TILER_HEAP_TERM:
      printer_kbase_ioctl_cs_tiler_heap_term((struct kbase_ioctl_cs_tiler_heap_term *)arg);
      break;
    case KBASE_IOCTL_CS_GET_GLB_IFACE:
      printer_kbase_ioctl_cs_get_glb_iface_out((union kbase_ioctl_cs_get_glb_iface *)arg);
      break;
    case KBASE_IOCTL_CS_CPU_QUEUE_DUMP:
      printer_kbase_ioctl_cs_cpu_queue_info((struct kbase_ioctl_cs_cpu_queue_info *)arg);
      break;
    case KBASE_IOCTL_MEM_ALLOC_EX:
      printer_kbase_ioctl_mem_alloc_ex_out((union kbase_ioctl_mem_alloc_ex *)arg);
      break;
    case KBASE_IOCTL_READ_USER_PAGE:
      printer_kbase_ioctl_read_user_page_out((union kbase_ioctl_read_user_page *)arg);
      break;
    case KBASE_IOCTL_VERSION_CHECK:
      printer_kbase_ioctl_version_check((struct kbase_ioctl_version_check *)arg);
      break;
    case KBASE_IOCTL_JOB_SUBMIT:
      printer_kbase_ioctl_job_submit((struct kbase_ioctl_job_submit *)arg);
      break;
    case KBASE_IOCTL_POST_TERM:
      break;
    case KBASE_IOCTL_SOFT_EVENT_UPDATE:
      printer_kbase_ioctl_soft_event_update((struct kbase_ioctl_soft_event_update *)arg);
      break;
    case KBASE_IOCTL_KINSTR_JM_FD:
      printer_kbase_kinstr_jm_fd_out((union kbase_kinstr_jm_fd *)arg);
      break;
    case KBASE_IOCTL_VERSION_CHECK_RESERVED:
      printer_kbase_ioctl_version_check((struct kbase_ioctl_version_check *)arg);
      break;
  }
 return 0;
}
