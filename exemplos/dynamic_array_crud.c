#include "dynamic_array.h"
#include <stdio.h>

static const int N = 1000000;

int main(void) {
    dynamic_array_t *arr;
    dynamic_array_initialize(&arr);
    for (int i = 0; i < N; i++) {
        int value = rand();
        dynamic_array_push_back(arr, value);
        printf("v[%d] = %d\n", i, arr->v[i]);
    }
    while (dynamic_array_size(arr) > 0) {
        printf("v[%zu] = %d\n", dynamic_array_size(arr) - 1,
               dynamic_array_back(arr));
        dynamic_array_pop_back(arr);
    }
    dynamic_array_delete(&arr);
    return 0;
}