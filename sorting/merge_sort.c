#include "merge_sort.h"
#include "../utils/alloc.h"
static void merge(int *v, int *v1, int *v2, size_t size) {

    size_t size_v1 = size / 2;
    size_t size_v2 = size - size_v1;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    /** Enquanto não chegar ao fim da primeira
     *  e da segunda metade **/
    for (i = 0; j < size_v1 && k < size_v2; i++) {
        /* Se o elemento da primeira metade
         * é menor ou igual ao da segunda metade,
         * insira-o no vetor resultado
         */
        if (v1[j] <= v2[k]) {
            v[i] = v1[j++];
        }
        /* Caso contrário, insira o elemento da
         * segunda metade no vetor resultado */
        else {
            v[i] = v2[k++];
        }
    }

    /** Se ainda  restam elementos na primeira partição **/
    while (j < size_v1) {
        /* Copiamos os elementos para o vetor resultado */
        v[i++] = v1[j++];
    }
    /** Se ainda  restam elementos na segunda partição **/
    while (k < size_v2) {
        /* Copiamos os elementos para o vetor resultado */
        v[i++] = v2[k++];
    }
}

void merge_sort(int *v, size_t size) {
    size_t mid;
    if (size > 1) {
        mid = size / 2;
        /* aloca espaço para os subvetores */
        int *v1 = mallocx(sizeof(int) * mid);
        int *v2 = mallocx(sizeof(int) * (size - mid));
        /* Copia os elementos de v para os subvetores */
        int i;
        for (i = 0; i < mid; i++) {
            v1[i] = v[i];
        }
        for (i = mid; i < size; i++) {
            v2[i - mid] = v[i];
        }
        /* Ordena recursivamente a primeira metade */
        merge_sort(v1, mid);
        /* Ordena recursivamente a segunda metade */
        merge_sort(v2, size - mid);
        /* Faz a junção das duas metades */
        merge(v, v1, v2, size);
        /* Libera o espaço alocado */
        free(v1);
        free(v2);
    }
}
