#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <stdbool.h>
#include <stddef.h>

typedef struct PoolAllocator {
  void *pool_memory;
  size_t block_size;
  size_t total_blocks;
  void *free_list;
  bool is_initialized;
} PoolAllocator;

void pool_allocator_init(PoolAllocator *allocator, void *memory_block,
                         size_t block_size, size_t block_count);

void *pool_allocator_allocate(PoolAllocator *allocator);

void pool_allocator_free(PoolAllocator *allocator, void *block_ptr);

#endif
