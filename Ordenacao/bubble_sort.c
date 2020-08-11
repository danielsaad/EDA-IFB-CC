#include "bubble_sort.h"

void swap(int* v,int i,int j){
    int t = v[i];
    v[i] = v[j];
    v[j] = t;
}

void bubble_sort(int *v, size_t size) {
  int swapped = 1;
  int i;
  for (i = 0; i < size - 1 && swapped; i++) {
    swapped = 0;
    int j;
    for (j = 0; j < size - i - 1; j++) {
      if (v[j] > v[j + 1]) {
        swap(v,j,j+1);
        swapped = 1;
      }
    }
  }
}
