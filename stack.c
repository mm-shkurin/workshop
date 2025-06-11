#include "stack.h"

void init_stack(Stack *stack) { stack->top = -1; }

int is_empty(Stack *stack) { return stack->top == -1; }

int is_full(Stack *stack) { return stack->top == STACK_CAPACITY - 1; }

int push(Stack *stack, int value) {
  if (is_full(stack))
    return -1;

  stack->top++;
  stack->data[stack->top] = value;
  return 0;
}

int pop(Stack *stack, int *value) {
  if (is_empty(stack))
    return -1;

  *value = stack->data[stack->top];
  stack->top--;
  return 0;
}

int peek(Stack *stack, int *value) {
  if (is_empty(stack))
    return -1;

  *value = stack->data[stack->top];
  return 0;
}
