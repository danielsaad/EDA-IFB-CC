#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"


void forall(list_t* l,void (*fn)(void*));


void divide_even_by_3(void* data){
    int* aux = data;
    if((*aux)%2==0){
        (*aux) = (*aux)/3;
    }
}

void zerar_pares(void* data){
    int* aux = data;
    if((*aux)%2==0){
        *aux = 0;
    }
}

void forall(list_t* l, void (*fn)(void* data)){
    list_node_t* it;
    for(it=l->head;it!=NULL;it=it->next){
        fn(it->data);
    }
}

void* construtor_int(void* data){
    void* ptr = malloc(sizeof(int));
    memcpy(ptr,data,sizeof(int));
    return ptr;
}

void destrutor_int(void* data){
    free(data);
}

int main(){
    list_t* l;
    list_initialize(&l,construtor_int,destrutor_int);
    int i;
    for(i=9;i<20;i++){
        list_append(l,&i);
    }
    forall(l,zerar_pares);
    list_node_t* it;
    for(it=l->head;it!=NULL;it=it->next){
        printf("%d->",*(int*)it->data);
    }
    printf("\n");
    list_delete(&l);
    return 0;
}