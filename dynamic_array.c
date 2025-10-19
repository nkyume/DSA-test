#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  long *arr;
  int size;
  size_t cap;
} DArray;

DArray *d_array_new() {
  DArray *array = malloc(sizeof(*array));
  if (!array) {
    fprintf(stderr, "Memory error at %s: %d\n", __FILE__, __LINE__);
    exit(EXIT_FAILURE);
  }
  array->arr = NULL;
  array->size = 0;
  array->cap = 0;
  return array;
}

void d_array_destroy(DArray *arr) {
  free(arr->arr);
  free(arr);
}

inline static void swap(long *a, long *b) {
  long tmp = *a;
  *a = *b;
  *b = tmp;
}

void d_array_insert(DArray *arr, size_t index, long value) {
  if (arr->size < (index + (arr->size - index))) {
    fprintf(stderr, "Index out of bounds in %s at %s: %d\n", __FILE__,
            __FUNCTION__, __LINE__);
    exit(EXIT_FAILURE);
  }
  if (arr->size >= arr->cap) {
    arr->cap = arr->cap ? arr->cap * 2 : 8;
    arr->arr = realloc(arr->arr, arr->cap * sizeof(*arr->arr));
    if (!arr->arr) {
      fprintf(stderr, "Mememory error in %s at %s: %d\n", __FILE__,
              __FUNCTION__, __LINE__);
      exit(EXIT_FAILURE);
    }
  }
  for (int i = arr->size; i > index; i--) {
    swap(arr->arr + i, arr->arr + i - 1);
  }
  arr->arr[index] = value;
  arr->size++;
}

long d_array_peek(DArray *arr, int index) {
  if (index > arr->size) {
    fprintf(stderr, "Index out of bounds in %s at %s: %d\n", __FILE__,
            __FUNCTION__, __LINE__);
    exit(EXIT_FAILURE);
  }
  return arr->arr[index];
}

long d_array_get(DArray *arr, int index) {
  long value;
  if (index > arr->size) {
    fprintf(stderr, "Index out of bounds in %s at %s: %d\n", __FILE__,
            __FUNCTION__, __LINE__);
    exit(EXIT_FAILURE);
  }
  value = arr->arr[index];
  for (size_t i = index + 1; i < arr->size; i++) {
    swap(arr->arr + i - 1, arr->arr + i);
  }
  arr->size--;
  return value;
}

void selection_sort(DArray *arr) {
  int min;
  if (arr->size < 2) {
    return;
  }
  for (int i = 0; i < arr->size; i++) {
    min = i;
    for (int j = i; j < arr->size; j++) {
      min = (arr->arr[min] < arr->arr[j]) ? min : j;
    }
    if (min == i) {
      continue;
    }
    swap(arr->arr + i, arr->arr + min);
  }
}

void insertion_sort(DArray *arr) {
  for (int i = 1; i < arr->size; i++) {
    long key = arr->arr[i];
    int j = i - 1;
    while (j >= 0 && key < arr->arr[j]) {
      arr->arr[j + 1] = arr->arr[j];
      j--;
    }
    arr->arr[j + 1] = key;
  }
}

void merge(long *arr, int start, int mid, int end) {
  int size = end - start + 1;
  long *tmp = malloc(sizeof(*tmp) * (size));
  int left, right;
  left = start;
  right = mid + 1;
  for (int i = 0; i < size; i++) {
    if (left > mid) {
      tmp[i] = arr[right];
      right++;
    } else if (right > end) {
      tmp[i] = arr[left];
      left++;
    } else if (arr[left] < arr[right]) {
      tmp[i] = arr[left];
      left++;
    } else {
      tmp[i] = arr[right];
      right++;
    }
  }
  for (int i = 0; i < size; i++) {
    arr[start + i] = tmp[i];
  }
  free(tmp);
}

void merge_sort(long *arr, int start, int end) {
  if (start >= end)
    return;
  int mid = (start + end) / 2;
  merge_sort(arr, start, mid);
  merge_sort(arr, mid + 1, end);
  merge(arr, start, mid, end);
}

void d_arr_merge_sort(DArray *arr) { merge_sort(arr->arr, 0, arr->size - 1); }

void quick_sort(long *arr, int start, int end) {
  if ((end - start) < 1)
    return;
  int left, right, pivot;
  pivot = (end + start) / 2;
  left = start;
  right = end - 1;
  swap(arr + pivot, arr + end);
  pivot = end;
  for (;;) {
    if (left > right) {
      break;
    }
    if (arr[left] > arr[right]) {
      swap(arr + left, arr + right);
    }
    if (arr[left] < arr[pivot])
      left++;
    if (arr[right] > arr[pivot])
      right--;
  }
  swap(arr + left, arr + pivot);
  quick_sort(arr, start, left);
  quick_sort(arr, left + 1, end);
};

void d_arr_quick_sort(DArray *arr) { quick_sort(arr->arr, 0, arr->size - 1); }
