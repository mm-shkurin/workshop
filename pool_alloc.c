#include "pool_alloc.h"
#include <assert.h>
#include <stdint.h>
#include <string.h>

void pool_allocator_init(PoolAllocator *allocator, void *memory_block,
                         size_t block_size, size_t block_count) {
  assert(allocator != NULL);
  assert(memory_block != NULL);
  assert(block_size >= sizeof(void *));
  assert(block_count > 0);
  uintptr_t addr = (uintptr_t)memory_block;
  size_t align = sizeof(void *);
  if (addr % align != 0) {
    addr += align - (addr % align);
  }
  memory_block = (void *)addr;

  allocator->pool_memory = memory_block;
  allocator->block_size = block_size;
  allocator->total_blocks = block_count;
  allocator->is_initialized = true;

  allocator->free_list = NULL;

  char *block_ptr = (char *)memory_block;
  for (size_t i = 0; i < block_count; ++i) {
    void **next_ptr = (void **)block_ptr;
    *next_ptr = allocator->free_list;
    allocator->free_list = block_ptr;
    block_ptr += block_size;
  }
}

void *pool_allocator_allocate(PoolAllocator *allocator) {
  assert(allocator != NULL);
  assert(allocator->is_initialized);

  if (allocator->free_list == NULL) {
    return NULL;
  }

  void *allocated_block = allocator->free_list;
  allocator->free_list = *(void **)allocator->free_list;

  return allocated_block;
}

void pool_allocator_free(PoolAllocator *allocator, void *block_ptr) {
  assert(allocator != NULL);
  assert(allocator->is_initialized);
  assert(block_ptr != NULL);

  char *pool_start = (char *)allocator->pool_memory;
  char *pool_end = pool_start + allocator->block_size * allocator->total_blocks;
  char *block = (char *)block_ptr;
  if (block < pool_start || block >= pool_end) {
    assert(false && "Invalid block pointer");
    return;
  }

  *(void **)block_ptr = allocator->free_list;
  allocator->free_list = block_ptr;
}
