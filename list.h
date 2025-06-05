#ifndef LIST_H
#define LIST_H

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct {
  Node *head;
  int size;
} LinkedList;

void init_list(LinkedList *list);

void add_first(LinkedList *list, int value);
void add_last(LinkedList *list, int value);
void add_at(LinkedList *list, int index, int value);

int remove_first(LinkedList *list);
int remove_last(LinkedList *list);
int remove_at(LinkedList *list, int index);

int get_at(LinkedList *list, int index);
int list_size(LinkedList *list);

void clear_list(LinkedList *list);

#endif