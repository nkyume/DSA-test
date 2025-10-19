#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Node *next;
  long value;
} Node;

typedef struct {
  Node *root;
  size_t size;
} List;

List *list_new() {
  List *list = malloc(sizeof(*list));
  if (!list) {
    fprintf(stderr, "Memory error in %s: %d\n", __FILE__, __LINE__);
    exit(EXIT_FAILURE);
  }
  list->root = NULL;
  list->size = 0;
  return list;
}

void list_destroy(List *list) {
  Node *tmp;
  Node *curr = list->root;
  while (curr) {
    tmp = curr;
    curr = tmp->next;
    free(tmp);
  }
  free(list);
}

void list_insert(List *list, long index, long value) {
  Node **curr = &list->root;
  Node *tmp;
  size_t size = list->size;
  if (index > list->size) {
    fprintf(stderr, "Index out of bounds in %s: %d\n", __FILE__, __LINE__);
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < size; i++) {
    if (i == index)
      break;
    curr = &(*curr)->next;
  }
  tmp = malloc(sizeof(*tmp));
  if (!tmp) {
    fprintf(stderr, "Memory error in %s: %d\n", __FILE__, __LINE__);
    exit(EXIT_FAILURE);
  }
  tmp->value = value;
  tmp->next = *curr;
  *curr = tmp;
  list->size++;
}

long list_peek(const List *list, size_t index) {
  Node *curr = list->root;
  if (index > list->size) {
    fprintf(stderr, "Index out of bounds in %s: %d\n", __FILE__, __LINE__);
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < index; i++) {
    curr = curr->next;
  }
  return curr->value;
}
