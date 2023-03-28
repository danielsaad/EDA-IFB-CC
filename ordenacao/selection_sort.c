#include "selection_sort.h"

void selection_sort(int* v, size_t size) {
    int min, tmp;
    for (int i = 0; i < size - 1; i++) {
        min = i;
        for (int j = i + 1; j < size; j++) {
            if(v[j] < v[min]) {
                min = j;
            }
        }
        tmp = v[min];
        v[min] = v[i];
        v[i] = tmp;
    }

}