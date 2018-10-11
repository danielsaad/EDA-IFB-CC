#include "list.h"

void forall(list_t* l,void (*fn)(void*));


void divide_even_by_3(void* data){
    int* aux = data
    if((*aux)%2==0){
        (*aux) = (*aux)/3;
    }
}

void forall(list_t* l, void (*fn)(void* data)){
    list_node_t* it;
    for(it=l->head;it!=NULL;it=it->next){
        fn(it->data);
    }
}