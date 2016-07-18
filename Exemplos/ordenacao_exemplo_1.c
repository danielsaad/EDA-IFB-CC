/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Este programa utiliza todos os métodos de ordenação
 * implementados pela biblioteca ED1.
**/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "alloc.h"
#include "sorting.h"

#define SIZE 10000 /**tamanho do vetor a ser gerado**/
#define MAX 10000 /**Maior numero possivel no vetor**/


int ordenado(int* vet, int tam){
    int i;
    for(i=0;i<tam-1;i++){
        if(vet[i]>vet[i+1])
            return(0);
    }
    return(1);
}

int main(void){
    srand(time(NULL));
    int i;
    int *v_copy,*v;
    size_t tam = SIZE;

    v_copy = callocx(tam,sizeof(int));
    v = calloc(tam,sizeof(int));
    /*Gera números aleatórios*/
    for(i=0;i<tam;i++){
        v_copy[i] = rand() % MAX;
    }


    memcpy(v,v_copy,sizeof(int)*tam);
    printf("Bubblesort...\n");
    bubble_sort(v,tam);
    printf("Fim...\n\n");
    if(!ordenado(v,tam)){
        printf("Bubblesort com problemas.\n");
        exit(EXIT_FAILURE);
    }


    memcpy(v,v_copy,sizeof(int)*tam);
    printf("Countingsort...\n");
    counting_sort(v,tam);
    printf("Fim...\n\n");
    if(!ordenado(v,tam)){
        printf("Countingsort com problemas.\n");
        exit(EXIT_FAILURE);
    }

    memcpy(v,v_copy,sizeof(int)*tam);
    printf("Heapsort...\n");
    heap_sort(v,tam);
    printf("Fim...\n\n");
    if(!ordenado(v,tam)){
        printf("Heapsort com problemas.\n");
        exit(EXIT_FAILURE);
    }


    memcpy(v,v_copy,sizeof(int)*tam);
    printf("Insertionsort...\n");
    insertion_sort(v,tam);
    printf("Fim...\n\n");
    if(!ordenado(v,tam)){
        printf("Insertionsort com problemas.\n");
        exit(EXIT_FAILURE);
    }

    memcpy(v,v_copy,sizeof(int)*tam);
    printf("Mergesort...\n");
    merge_sort(v,tam);
    printf("Fim...\n\n");
    if(!ordenado(v,tam)){
        printf("Mergesort com problemas.\n");
        exit(EXIT_FAILURE);
    }

    memcpy(v,v_copy,sizeof(int)*tam);
    printf("Quicksort...\n");
    quick_sort(v,tam);
    printf("Fim...\n\n");
    if(!ordenado(v,tam)){
        printf("Quicksort com problemas.\n");
        exit(EXIT_FAILURE);
    }

    memcpy(v,v_copy,sizeof(int)*tam);
    printf("Radixsort...\n");
    radix_sort(v,tam);
    printf("Fim...\n\n");
    if(!ordenado(v,tam)){
        printf("Radixsort com problemas.\n");
        exit(EXIT_FAILURE);
    }

    free(v_copy);
    free(v);
    return(0);
}

