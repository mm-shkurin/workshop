#include "stack.h"
#include <assert.h>
#include <stdio.h>

void test_stack_operations() {
  Stack stack;
  init_stack(&stack);
  int value;

  assert(is_empty(&stack) == 1);
  assert(pop(&stack, &value) == -1);
  assert(peek(&stack, &value) == -1);

  assert(push(&stack, 10) == 0);
  assert(is_empty(&stack) == 0);
  assert(peek(&stack, &value) == 0 && value == 10);

  assert(push(&stack, 20) == 0);
  assert(peek(&stack, &value) == 0 && value == 20);

  assert(push(&stack, 30) == 0);
  assert(peek(&stack, &value) == 0 && value == 30);

  assert(pop(&stack, &value) == 0 && value == 30);
  assert(peek(&stack, &value) == 0 && value == 20);

  assert(pop(&stack, &value) == 0 && value == 20);
  assert(peek(&stack, &value) == 0 && value == 10);

  assert(pop(&stack, &value) == 0 && value == 10);
  assert(is_empty(&stack) == 1);
}

void test_stack_full() {
  Stack stack;
  init_stack(&stack);
  int value;

  for (int i = 0; i < STACK_CAPACITY; i++) {
    assert(push(&stack, i) == 0);
  }

  assert(is_full(&stack) == 1);
  assert(peek(&stack, &value) == 0 && value == STACK_CAPACITY - 1);

  assert(push(&stack, 100) == -1);
  assert(peek(&stack, &value) == 0 && value == STACK_CAPACITY - 1);

  for (int i = STACK_CAPACITY - 1; i >= 0; i--) {
    assert(pop(&stack, &value) == 0 && value == i);
  }

  assert(is_empty(&stack) == 1);
}

int main() {
  test_stack_operations();
  test_stack_full();

  printf("All stack tests passed successfully!\n");
  return 0;
}
