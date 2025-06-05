#include "linear_alloc.h"
#include <assert.h>

void linear_allocator_init(LinearAllocator *allocator, void *memory_block,
                           size_t block_size) {
  assert(allocator != NULL);
  assert(memory_block != NULL);
  assert(block_size > 0);

  allocator->linalloc_buffer = memory_block;
  allocator->linalloc_total_size = block_size;
  allocator->linalloc_offset = 0;
  allocator->linalloc_is_initialized = true;
}

void *linear_allocator_allocate(LinearAllocator *allocator,
                                size_t requested_size) {
  assert(allocator != NULL);
  assert(allocator->linalloc_is_initialized);

  if (requested_size == 0) {
    return NULL;
  }

  if (allocator->linalloc_offset + requested_size >
      allocator->linalloc_total_size) {
    return NULL;
  }

  void *allocated_ptr =
      (char *)allocator->linalloc_buffer + allocator->linalloc_offset;
  allocator->linalloc_offset += requested_size;
  return allocated_ptr;
}

void linear_allocator_reset(LinearAllocator *allocator) {
  assert(allocator != NULL);
  allocator->linalloc_offset = 0;
}