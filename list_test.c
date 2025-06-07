#include "list.h"
#include <assert.h>
#include <stdio.h>

void test_add_operations() {
  LinkedList list;
  init_list(&list);

  add_first(&list, 10);
  assert(list_size(&list) == 1);
  assert(get_at(&list, 0) == 10);

  add_last(&list, 20);
  assert(list_size(&list) == 2);
  assert(get_at(&list, 1) == 20);

  add_at(&list, 1, 15);
  assert(list_size(&list) == 3);
  assert(get_at(&list, 1) == 15);

  clear_list(&list);
}

void test_remove_operations() {
  LinkedList list;
  init_list(&list);

  add_last(&list, 10);
  add_last(&list, 20);
  add_last(&list, 30);

  assert(remove_first(&list) == 10);
  assert(list_size(&list) == 2);

  assert(remove_last(&list) == 30);
  assert(list_size(&list) == 1);

  add_first(&list, 5);
  add_last(&list, 25);
  assert(remove_at(&list, 1) == 20);
  assert(list_size(&list) == 2);

  clear_list(&list);
}

void test_edge_cases() {
  LinkedList list;
  init_list(&list);

  assert(remove_first(&list) == -1);
  assert(remove_last(&list) == -1);
  assert(remove_at(&list, 0) == -1);
  assert(list_size(&list) == 0);

  add_first(&list, 10);
  assert(get_at(&list, -1) == -1);
  assert(get_at(&list, 1) == -1);

  clear_list(&list);
}

int main() {
  test_add_operations();
  test_remove_operations();
  test_edge_cases();

  printf("All linked list tests passed successfully!\n");
  return 0;
}
