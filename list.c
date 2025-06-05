#include "list.h"
#include <stdlib.h>

void init_list(LinkedList *list) {
  list->head = NULL;
  list->size = 0;
}

void add_first(LinkedList *list, int value) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = value;
  new_node->next = list->head;
  list->head = new_node;
  list->size++;
}

void add_last(LinkedList *list, int value) {
  if (list->head == NULL) {
    add_first(list, value);
    return;
  }

  Node *current = list->head;
  while (current->next != NULL) {
    current = current->next;
  }

  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = value;
  new_node->next = NULL;
  current->next = new_node;
  list->size++;
}

void add_at(LinkedList *list, int index, int value) {
  if (index < 0 || index > list->size)
    return;
  if (index == 0) {
    add_first(list, value);
    return;
  }
  if (index == list->size) {
    add_last(list, value);
    return;
  }

  Node *current = list->head;
  for (int i = 0; i < index - 1; i++) {
    current = current->next;
  }

  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = value;
  new_node->next = current->next;
  current->next = new_node;
  list->size++;
}

int remove_first(LinkedList *list) {
  if (list->head == NULL)
    return -1;

  Node *temp = list->head;
  int value = temp->data;
  list->head = temp->next;
  free(temp);
  list->size--;
  return value;
}

int remove_last(LinkedList *list) {
  if (list->head == NULL)
    return -1;
  if (list->head->next == NULL)
    return remove_first(list);

  Node *current = list->head;
  while (current->next->next != NULL) {
    current = current->next;
  }

  int value = current->next->data;
  free(current->next);
  current->next = NULL;
  list->size--;
  return value;
}

int remove_at(LinkedList *list, int index) {
  if (index < 0 || index >= list->size)
    return -1;
  if (index == 0)
    return remove_first(list);
  if (index == list->size - 1)
    return remove_last(list);

  Node *current = list->head;
  for (int i = 0; i < index - 1; i++) {
    current = current->next;
  }

  Node *temp = current->next;
  int value = temp->data;
  current->next = temp->next;
  free(temp);
  list->size--;
  return value;
}

int get_at(LinkedList *list, int index) {
  if (index < 0 || index >= list->size)
    return -1;

  Node *current = list->head;
  for (int i = 0; i < index; i++) {
    current = current->next;
  }
  return current->data;
}

int list_size(LinkedList *list) { return list->size; }

void clear_list(LinkedList *list) {
  while (list->head != NULL) {
    remove_first(list);
  }
}