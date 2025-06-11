#include "array.h"
#include "linear_alloc.h"
#include <assert.h>
#include <stdio.h>

int main() {
  printf("Testing ArrayList implementation\n");

  char memory[1024];
  LinearAllocator allocator;
  linear_allocator_init(&allocator, memory, sizeof(memory));

  ArrayList list;
  array_init(&list, &allocator, sizeof(int));

  assert(list.size == 0);
  assert(list.capacity == INITIAL_CAPACITY);

  int values[] = {1, 2, 3, 4, 5};
  for (int i = 0; i < 5; i++) {
    array_add(&list, &values[i], i);
  }
  assert(list.size == 5);

  for (int i = 0; i < 5; i++) {
    int *val = array_get(&list, i);
    assert(val && *val == values[i]);
  }

  int new_value = 10;
  array_add(&list, &new_value, 2);
  assert(list.size == 6);
  assert(*(int*)array_get(&list, 2) == 10);
  assert(*(int*)array_get(&list, 3) == 3);

  array_del(&list, 2);
  assert(list.size == 5);
  assert(*(int*)array_get(&list, 2) == 3);

  printf("All tests passed!\n");
  return 0;
}
