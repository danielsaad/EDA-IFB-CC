#include "merge_sort.h"
#include "../Utils/alloc.h"
static void merge(int* v, size_t size){
	int mid;
	int i, j, k;
	int* tmp;
 
    tmp = mallocx (size * sizeof(int));
    mid = size / 2;
	i = 0;
	j = mid;
	k = 0;
    while (i < mid && j < size){
        if (v[i] <= v[j]){
            tmp[k] = v[i++];
		}
        else{
            tmp[k] = v[j++];
		}
		++k;
	}
 
    if (i == mid){
        while (j < size) {
            tmp[k++] = v[j++];
		}
	}
    else{
        while (i < mid){
            tmp[k++] = v[i++];
 
		}
	}
	
    for (i = 0; i < size; ++i) {
        v[i] = tmp[i];
	}
    free(tmp);
}
 
void merge_sort(int* v, size_t size){
  size_t mid;
  if (size > 1){
    mid = size / 2;
    merge_sort(v, mid);
    merge_sort(v + mid, size - mid);
    merge(v, size);
  }
}
