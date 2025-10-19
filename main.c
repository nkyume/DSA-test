#include <cstdlib>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
  struct Node *next;
  long value;
} Node;

typedef struct {
  Node *root;
  size_t size;
} List;

List *list_new();
void list_insert(List *, long, long);
long list_peek(List *, size_t);
void list_destroy(List *);

typedef struct {
  long *arr;
  size_t size;
  size_t cap;
} DArray;

DArray *d_array_new();
void d_array_insert(DArray *, size_t, long);
long d_array_peek(DArray *, size_t);
void d_array_destroy(DArray *);
long d_array_get(DArray *, size_t);

void selection_sort(DArray *);
void insertion_sort(DArray *);
void d_arr_merge_sort(DArray *);

enum { first = 1000, second = 10000, third = 100000 };

void bench_list() {
  long end, start;
  int test = 0;

  List *list;
  DArray *arr;

  for (int i = 0; i < 3; i++) {
    switch (i) {
    case 0:
      test = first;
      break;
    case 1:
      test = second;
      break;
    case 2:
      test = third;
      break;
    }
    start = clock();
    list = list_new();
    for (int i = 0; i < test; i++) {
      list_insert(list, 0, i);
    }
    list_destroy(list);
    end = clock();
    printf("LIST | %d insertions in the beginning time: %fms\n", test,
           (double)(end - start) * 1000 / CLOCKS_PER_SEC);
  }

  for (int i = 0; i < 3; i++) {
    switch (i) {
    case 0:
      test = first;
      break;
    case 1:
      test = second;
      break;
    case 2:
      test = third;
      break;
    }
    start = clock();
    list = list_new();
    for (int i = 0; i < test; i++) {
      list_insert(list, list->size / 2, i);
    }
    list_destroy(list);
    end = clock();
    printf("LIST | %d insertions in the middle time: %fms\n", test,
           (double)(end - start) * 1000 / CLOCKS_PER_SEC);
  }

  for (int i = 0; i < 3; i++) {
    switch (i) {
    case 0:
      test = first;
      break;
    case 1:
      test = second;
      break;
    case 2:
      test = third;
      break;
    }
    start = clock();
    list = list_new();
    for (int i = 0; i < test; i++) {
      list_insert(list, list->size, i);
    }
    list_destroy(list);
    end = clock();
    printf("LIST | %d insertions at the end time: %fms\n", test,
           (double)(end - start) * 1000 / CLOCKS_PER_SEC);
  }

  for (int i = 0; i < 3; i++) {
    switch (i) {
    case 0:
      test = first;
      break;
    case 1:
      test = second;
      break;
    case 2:
      test = third;
      break;
    }
    start = clock();
    arr = d_array_new();
    for (int i = 0; i < test; i++) {
      d_array_insert(arr, 0, i);
    }
    d_array_destroy(arr);
    end = clock();
    printf("ARRAY | %d insertions in the beginning time: %fms\n", test,
           (double)(end - start) * 1000 / CLOCKS_PER_SEC);
  }

  for (int i = 0; i < 3; i++) {
    switch (i) {
    case 0:
      test = first;
      break;
    case 1:
      test = second;
      break;
    case 2:
      test = third;
      break;
    }
    start = clock();
    arr = d_array_new();
    for (int i = 0; i < test; i++) {
      d_array_insert(arr, arr->size / 2, i);
    }
    d_array_destroy(arr);
    end = clock();
    printf("ARRAY | %d insertions in the middle time: %fms\n", test,
           (double)(end - start) * 1000 / CLOCKS_PER_SEC);
  }

  for (int i = 0; i < 3; i++) {
    switch (i) {
    case 0:
      test = first;
      break;
    case 1:
      test = second;
      break;
    case 2:
      test = third;
      break;
    }
    start = clock();
    arr = d_array_new();
    for (int i = 0; i < test; i++) {
      d_array_insert(arr, arr->size, i);
    }
    d_array_destroy(arr);
    end = clock();
    printf("ARRAY | %d insertions at the end time: %fms\n", test,
           (double)(end - start) * 1000 / CLOCKS_PER_SEC);
  }
}

void bench_sort() {
  DArray *arr;
  long start, end;
  arr = d_array_new();
  start = clock();
  for (int i = 0; i < 1000; i++) {
    d_array_insert(arr, 0, i);
  }
  d_arr_merge_sort(arr);
  d_array_destroy(arr);
  end = clock();
  printf("MERGE | 1.000 elements %fms\n",
         (double)(end - start) * 1000 / CLOCKS_PER_SEC);

  start = clock();
  arr = d_array_new();
  for (int i = 0; i < 1000; i++) {
    d_array_insert(arr, 0, i);
  }
  insertion_sort(arr);
  d_array_destroy(arr);
  end = clock();
  printf("INSERTION | 1.000 elements %fms\n",
         (double)(end - start) * 1000 / CLOCKS_PER_SEC);

  arr = d_array_new();
  start = clock();
  for (int i = 0; i < 100000; i++) {
    d_array_insert(arr, 0, i);
  }
  d_arr_merge_sort(arr);
  d_array_destroy(arr);
  end = clock();
  printf("MERGE | 100.000 elements %fms\n",
         (double)(end - start) * 1000 / CLOCKS_PER_SEC);

  start = clock();
  arr = d_array_new();
  for (int i = 0; i < 100000; i++) {
    d_array_insert(arr, 0, i);
  }
  insertion_sort(arr);
  d_array_destroy(arr);
  end = clock();
  printf("INSERTION | 100.000 elements %fms\n",
         (double)(end - start) * 1000 / CLOCKS_PER_SEC);
}

int main() {
  bench_sort();
  exit(EXIT_SUCCESS);
}
