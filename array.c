#include "array.h"
#include "linear_alloc.h"
#include <assert.h>
#include <string.h>

void array_init(ArrayList *list, LinearAllocator *allocator, size_t element_size) {
  assert(list != NULL);
  assert(allocator != NULL);
  assert(element_size > 0);

  list->element_size = element_size;
  list->data = linear_allocator_allocate(allocator, INITIAL_CAPACITY * element_size);
  list->capacity = list->data ? INITIAL_CAPACITY : 0;
  list->size = 0;
  list->allocator = allocator;
}

static int ensure_capacity(ArrayList *list) {
  if (list->size < list->capacity) {
    return 1;
  }

  size_t new_capacity = list->capacity * 2;
  void *new_data = linear_allocator_allocate(
      list->allocator, new_capacity * list->element_size);

  if (!new_data) {
    return 0;
  }

  memcpy(new_data, list->data, list->size * list->element_size);
  list->data = new_data;
  list->capacity = new_capacity;
  return 1;
}

void array_add(ArrayList *list, const void *data, size_t index) {
  assert(list != NULL);
  assert(data != NULL);
  assert(index <= list->size);

  if (!ensure_capacity(list)) {
    return;
  }

  char *base_ptr = (char *)list->data;
  size_t element_size = list->element_size;

  if (index < list->size) {
    memmove(base_ptr + (index + 1) * element_size,
            base_ptr + index * element_size,
            (list->size - index) * element_size);
  }

  memcpy(base_ptr + index * element_size, data, element_size);
  list->size++;
}

void *array_get(ArrayList *list, size_t index) {
  if (!list || index >= list->size) {
    return NULL;
  }
  return (char *)list->data + index * list->element_size;
}

void array_del(ArrayList *list, size_t index) {
  if (!list || index >= list->size) {
    return;
  }

  char *base_ptr = (char *)list->data;
  size_t element_size = list->element_size;

  if (index < list->size - 1) {
    memmove(base_ptr + index * element_size,
            base_ptr + (index + 1) * element_size,
            (list->size - index - 1) * element_size);
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
