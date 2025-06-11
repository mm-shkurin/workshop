#include "stack.h"

void init_stack(Stack *stack) { stack->top = -1; }

int is_empty(Stack *stack) { return stack->top == -1; }

int is_full(Stack *stack) { return stack->top == STACK_CAPACITY - 1; }

void push(Stack *stack, int value) {
  if (is_full(stack))
    return;

  stack->top++;
  stack->data[stack->top] = value;
}

int pop(Stack *stack) {
  if (is_empty(stack))
    return -1;

  int value = stack->data[stack->top];
  stack->top--;
  return value;
}

int peek(Stack *stack) {
  if (is_empty(stack))
    return -1;
  return stack->data[stack->top];
}
