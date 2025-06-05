#include "pool_alloc.h"
#include <stdio.h>
#include <assert.h>

int main() {
    printf("Running pool allocator tests...\n");

    #define BLOCK_SIZE 64
    #define BLOCK_COUNT 10
    char test_memory[BLOCK_SIZE * BLOCK_COUNT];
    
    PoolAllocator test_allocator;
    pool_allocator_init(&test_allocator, test_memory, BLOCK_SIZE, BLOCK_COUNT);

    void* blocks[BLOCK_COUNT];
    for (int i = 0; i < BLOCK_COUNT; i++) {
        blocks[i] = pool_allocator_allocate(&test_allocator);
        assert(blocks[i] != NULL && "Allocation failed");
        printf("Allocated block %d at %p\n", i, blocks[i]);
    }

    void* should_be_null = pool_allocator_allocate(&test_allocator);
    assert(should_be_null == NULL && "Should return NULL when no free blocks");

    for (int i = 0; i < BLOCK_COUNT; i++) {
        pool_allocator_free(&test_allocator, blocks[i]);
        printf("Freed block %d at %p\n", i, blocks[i]);
    }

    for (int i = 0; i < BLOCK_COUNT; i++) {
        blocks[i] = pool_allocator_allocate(&test_allocator);
        assert(blocks[i] != NULL && "Re-allocation failed");
        printf("Re-allocated block %d at %p\n", i, blocks[i]);
    }

    pool_allocator_free(&test_allocator, blocks[3]);
    void* reused_block = pool_allocator_allocate(&test_allocator);
    assert(reused_block == blocks[3] && "Should reuse freed block");
    printf("Reused freed block at %p\n", reused_block);

    printf("All tests passed!\n");
    return 0;
}