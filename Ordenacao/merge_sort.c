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

    /** Enquanto não chegar ao fim da primeira
     *  e da segunda metade **/
    while (i < mid && j < size){
        /* Se o elemento da primeira metade
         * é menor ou igual ao da segunda metade,
         * insira-o no vetor resultado
         */
        if (v[i] <= v[j]){
            tmp[k] = v[i++];
        }
        /* Caso contrário, insira o elemento da
         * segunda metade no vetor resultado */
        else{
            tmp[k] = v[j++];
        }
        ++k;
    }

    /** Se ainda  restam elementos na segunda partição **/
    if (i == mid){
        /* Jogamos os elementos da segunda partição
         * no vetor resultado */
        while (j < size) {
            tmp[k++] = v[j++];
        }
    }
    else{
        /* Restam elementos na primeira partição */

        /* Jogamos os elementos da primeira partição
         * no vetor resultado */
        while (i < mid){
            tmp[k++] = v[i++];

        }
    }

    /* Copiamos o conteúdo do vetor temporário
     * para o vetor original */
    for (i = 0; i < size; ++i) {
        v[i] = tmp[i];
    }
    /* Liberamos o vetor temporário */
    free(tmp);
}

void merge_sort(int* v, size_t size){
    size_t mid;
    if (size > 1){
        mid = size / 2;
        /* Ordena recursivamente a primeira metade */
        merge_sort(v, mid);
        /* Ordena recursivamente a segunda metade */
        merge_sort(v + mid, size - mid);
        /* Faz a junção das duas metades */
        merge(v, size);
    }
}
