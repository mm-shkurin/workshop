#ifndef ARRAY_H
#define ARRAY_H

#include "linear_alloc.h"
#include <stddef.h>

#define INITIAL_CAPACITY 8

typedef struct {
  void **data;
  size_t capacity;
  size_t size;
  LinearAllocator *allocator;
} ArrayList;

void array_init(ArrayList *list, LinearAllocator *allocator);
void array_add(ArrayList *list, void *data, size_t index);
void *array_get(ArrayList *list, size_t index);
void array_del(ArrayList *list, size_t index);
void array_free(ArrayList *list);

#endif