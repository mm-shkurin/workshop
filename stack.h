#ifndef STACK_H
#define STACK_H

#define STACK_CAPACITY 100

typedef struct {
  int data[STACK_CAPACITY];
  int top;
} Stack;

void init_stack(Stack *stack);
int is_empty(Stack *stack);
int is_full(Stack *stack);
int push(Stack *stack, int value);
int pop(Stack *stack, int *value);
int peek(Stack *stack, int *value);

#endif
