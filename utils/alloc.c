#include <stdio.h>
#include "alloc.h"


void* mallocx(size_t n){
    void* ptr = malloc(n);
    if(ptr==NULL){
        printf("Erro mallocx");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void* callocx(size_t n,size_t s){
    void* ptr = calloc(n,s);
    if(ptr==NULL){
        printf("Erro callocx");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void* reallocx(void* ptr,size_t n){
    void* aux = realloc(ptr,n);
    if(aux==NULL && n!=0){
        printf("Erro reallocx");
        exit(EXIT_FAILURE);
    }
    return aux;
}

