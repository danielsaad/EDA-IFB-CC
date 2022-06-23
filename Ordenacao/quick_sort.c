#include "quick_sort.h"

static void swap(int *v, int i, int j);
static size_t partition(int *vet, int esq,int dir,int pivot);
static void quick_sort_helper(int*v, int l,int r);

static void swap(int *v, int i, int j){
    int t = v[i];
    v[i] = v[j];
    v[j] = t;
}

static size_t partition(int *vet, int esq,int dir,int pivot){
    size_t pos, i;
    swap(vet, pivot, dir);
    pos = esq;
    for(i = esq; i < dir; i++){
        if (vet[i] < vet[dir]){
            swap(vet, i, pos);
            pos++;
        }
    }
    swap(vet, dir, pos);
    return pos;
}

void quick_sort_helper(int*v, int l,int r){
    if (l < r){
        size_t pos = partition(v,l,r,r);
        quick_sort_helper(v, l, pos - 1);
        quick_sort_helper(v, pos + 1, r);
    }
}

void quick_sort(int *v, size_t size){
    quick_sort_helper(v,0,size-1);
}
