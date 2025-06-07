#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  void *linalloc_buffer;
  size_t linalloc_total_size;
  size_t linalloc_offset;
  bool linalloc_is_initialized;
} LinearAllocator;

void linear_allocator_init(LinearAllocator *allocator, void *memory_block,
                           size_t block_size);

void *linear_allocator_allocate(LinearAllocator *allocator,
                                size_t requested_size);

void linear_allocator_reset(LinearAllocator *allocator);

#endif
