#include "linear_alloc.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main() {
  printf("Running linear allocator tests...\n");

  char test_memory_block[1024];
  LinearAllocator test_allocator;
  linear_allocator_init(&test_allocator, test_memory_block,
                        sizeof(test_memory_block));

  int *test_int_array = (int *)linear_allocator_allocate(&test_allocator,
                                                         10 * sizeof(int));
  assert(test_int_array != NULL && "Allocation failed!");

  for (int i = 0; i < 10; i++) {
    test_int_array[i] = i;
  }

  void *test_failed_allocation =
      linear_allocator_allocate(&test_allocator, 2000);
  assert(test_failed_allocation == NULL &&
         "Allocation should fail (not enough memory)");

  linear_allocator_reset(&test_allocator);
  char *test_string = (char *)linear_allocator_allocate(&test_allocator, 100);
  assert(test_string != NULL && "Allocation after reset failed!");
  strcpy(test_string, "Test string");
  printf("String after reset: %s\n", test_string);

  void *test_zero_allocation = linear_allocator_allocate(&test_allocator, 0);
  assert(test_zero_allocation == NULL &&
         "Zero-size allocation should return NULL");

  printf("All tests passed!\n");
  return 0;
}
