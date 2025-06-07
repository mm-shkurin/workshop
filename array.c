#include "array.h"
#include "linear_alloc.h"
#include <assert.h>
#include <string.h>


void array_init(ArrayList *list, LinearAllocator *allocator) {
  assert(list != NULL);
  assert(allocator != NULL);

  list->data =
      linear_allocator_allocate(allocator, INITIAL_CAPACITY * sizeof(void *));
  list->capacity = list->data ? INITIAL_CAPACITY : 0;
  list->size = 0;
  list->allocator = allocator;
}

static int ensure_capacity(ArrayList *list) {
  if (list->size < list->capacity) {
    return 1;
  }

  size_t new_capacity = list->capacity * 2;
  void **new_data =
      linear_allocator_allocate(list->allocator, new_capacity * sizeof(void *));

  if (!new_data) {
    return 0;
  }

  memcpy(new_data, list->data, list->size * sizeof(void *));
  list->data = new_data;
  list->capacity = new_capacity;
  return 1;
}

void array_add(ArrayList *list, void *data, size_t index) {
  assert(list != NULL);
  assert(index <= list->size);

  if (!ensure_capacity(list)) {
    return;
  }

  if (index < list->size) {
    memmove(&list->data[index + 1], &list->data[index],
            (list->size - index) * sizeof(void *));
  }

  list->data[index] = data;
  list->size++;
}
void *array_get(ArrayList *list, size_t index) {
  if (!list || index >= list->size) {
    return NULL;
  }
  return list->data[index];
}

void array_del(ArrayList *list, size_t index) {
  if (!list || index >= list->size) {
    return;
  }
  if (index < list->size - 1) {
    memmove(&list->data[index], &list->data[index + 1],
            (list->size - index - 1) * sizeof(void *));
  }

  list->size--;
}

void array_free(ArrayList *list) {
  if (list) {
    list->size = 0;
    list->capacity = 0;
    list->data = NULL;
  }
}
