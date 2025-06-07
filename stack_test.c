#include "stack.h"
#include <assert.h>
#include <stdio.h>

void test_stack_operations() {
  Stack stack;
  init_stack(&stack);

  assert(is_empty(&stack) == 1);
  assert(pop(&stack) == -1);
  assert(peek(&stack) == -1);

  push(&stack, 10);
  assert(is_empty(&stack) == 0);
  assert(peek(&stack) == 10);

  push(&stack, 20);
  assert(peek(&stack) == 20);

  push(&stack, 30);
  assert(peek(&stack) == 30);

  assert(pop(&stack) == 30);
  assert(peek(&stack) == 20);

  assert(pop(&stack) == 20);
  assert(peek(&stack) == 10);

  assert(pop(&stack) == 10);
  assert(is_empty(&stack) == 1);
}

void test_stack_full() {
  Stack stack;
  init_stack(&stack);

  for (int i = 0; i < STACK_CAPACITY; i++) {
    push(&stack, i);
  }

  assert(is_full(&stack) == 1);
  assert(peek(&stack) == STACK_CAPACITY - 1);

  push(&stack, 100);
  assert(peek(&stack) == STACK_CAPACITY - 1);

  for (int i = STACK_CAPACITY - 1; i >= 0; i--) {
    assert(pop(&stack) == i);
  }

  assert(is_empty(&stack) == 1);
}

int main() {
  test_stack_operations();
  test_stack_full();

  printf("All stack tests passed successfully!\n");
  return 0;
}
