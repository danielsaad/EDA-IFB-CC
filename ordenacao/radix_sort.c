#include <string.h>
#include "radix_sort.h"
#include "../utils/alloc.h"

void radix_sort(int* v, size_t size){
    int i;
    int* c;
    int bucket[10] = {0,0,0,0,0,0,0,0,0,0};
    int largest = v[0];
    int exp = 1;
 
    c = mallocx(sizeof(int)*size);
    for (i = 0; i < size; i++) {
        if (v[i] > largest)
            largest = v[i];
    }
 
    while (largest/exp > 0){
        memset(bucket,0,sizeof(int)*10);
        for (i = 0; i < size; i++)
            bucket[(v[i] / exp) % 10]++;
    	for (i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1];
        for (i = size - 1; i >= 0; i--)
            c[--bucket[(v[i] / exp) % 10]] = v[i];
        for (i = 0; i < size; i++)
            v[i] = c[i];
    	exp *= 10;
    }
    free(c);
}
