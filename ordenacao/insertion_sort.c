#include "insertion_sort.h"

void insertion_sort(int *v, size_t size) {
    int i, j, chosen;
    for (i = 1; i < size; i++) {
        chosen = v[i];
        for (j = i - 1; (j >= 0) && chosen < v[j]; j--) {
            v[j + 1] = v[j];
        }
        v[j + 1] = chosen;
    }
}
