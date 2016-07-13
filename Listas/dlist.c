#include <assert.h>
#include "dlist.h"
#include "../Utils/alloc.h"



dlist_node_t* dlist_node_new(void* data,dlist_node_constructor_fn constructor){
    dlist_node_t* new_node =  mallocx(sizeof(dlist_node_t));
    new_node->data = constructor(data);
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

/**Inicializa a lista duplamente encadeada e seus membros**/
void dlist_initialize(dlist_t** l,dlist_node_constructor_fn constructor,
    dlist_node_destructor_fn destructor){
    (*l) = mallocx(sizeof(dlist_t));
    (*l)->head = NULL;
    (*l)->tail = NULL;
    (*l)->size = 0;
    (*l)->constructor = constructor;
    (*l)->destructor = destructor;
}

void dlist_delete(dlist_t** l){
    while(!dlist_empty(*l)){
        dlist_remove_head(*l);
    }
    free(*l);
    *l = NULL;
}

void dlist_insert(dlist_t* l,void* data,size_t i){
    assert(i<=dlist_size(l));
    dlist_node_t* new_node = dlist_node_new(data,l->constructor);
    if(dlist_empty(l)){
        /*Se a dlista está vazia, cabeça e cauda apontam para o mesmo lugar*/
        l->head = new_node;
        l->tail = new_node;
    }
    else if(i==0){
        /*Inserção na cabeça*/
        new_node->next = l->head;
        l->head->prev = new_node;
        l->head = new_node;
    }
    else if(i==dlist_size(l)){
        /*Inserção na cauda*/
        new_node->prev = l->tail;
        l->tail->next = new_node;
        l->tail = new_node;
    }
    else{
        /*Inserção no meio da lista*/
        /*Precisamos encontrar o elemento que antecede a posição i*/
        dlist_iterator_t it = l->head;
        int k;
        for(k=0;k<i-1;k++){
            it = it->next;
        }
        /*aux agora aponta pro elemento da posição i-1*/
        new_node->next = it->next;
        new_node->prev = it;
        it->next->prev = new_node;
        it->next = new_node;
    }
    l->size++;
}

/** Insere um elemento na cabeça da dlista **/
void dlist_prepend(dlist_t* l,void* data){
    dlist_node_t* new_node = dlist_node_new(data,l->constructor);
    new_node->next = l->head;
    if(dlist_empty(l)){
        l->tail = new_node;
    }
    else{
        l->head->prev = new_node;
    }
    l->head = new_node;
    l->size++;
}

/**Insere um elemento na cauda da dlista **/
void dlist_append(dlist_t* l, void* data){
    dlist_node_t* new_node = dlist_node_new(data,l->constructor);
    new_node->prev = l->tail;
    if(dlist_empty(l)){
        l->head = new_node;
    }
    else{
        l->tail->next = new_node;
    }
    l->tail = new_node;
    l->size++;
}

/**Remove o elemento da posição i da dlista**/
void dlist_remove(dlist_t* l,size_t i){
    assert(!dlist_empty(l) && i<dlist_size(l));
    dlist_node_t* node;
    if(dlist_size(l)==1){
        /*Remoção em uma dlista com um elemento*/
        node = l->head;
        l->head = NULL;
        l->tail = NULL;
    }
    else if(i==0){
        /*Remoção na cabeça*/
        node = l->head;
        l->head = l->head->next;
        l->head->prev = NULL;
    }
    else if(i==dlist_size(l)-1){
        node = l->tail;
        l->tail = l->tail->prev;
        l->tail->next = NULL;
    }
    else{
        dlist_iterator_t it = l->head;
        int k;
        for(k=0;k<i-1;k++){
            it = it->next;
        }
        node = it->next;
        it->next = node->next;
        node->next->prev = it;
    }
    l->destructor(node->data);
    free(node);
    l->size--;

}

void dlist_remove_head(dlist_t* l){
    assert(!dlist_empty(l));
    dlist_iterator_t it = l->head;
    l->head = l->head->next;
    if(dlist_size(l)==1){
        l->tail = NULL;
    }
    else{
        l->head->prev = NULL;
    }
    l->destructor(it->data);
    free(it);
}

void dlist_remove_tail(dlist_t* l){
    assert(!dlist_empty(l));
    dlist_iterator_t it = l->tail;
    if(dlist_size(l)==1){
        l->head = NULL;
        l->tail = NULL;
    }
    else{
        l->tail = l->tail->prev;
        l->tail->next = NULL;
    }
    l->destructor(it->data);
    free(it);
}

void* dlist_access(dlist_t* l,size_t i){
    assert(!dlist_empty(l) && i<dlist_size(l));
    dlist_iterator_t it = l->head;
    int j;
    for(j=0;j<i;j++){
        it = it->next;
    }
    return(it->data);
}

void* dlist_access_head(dlist_t* l){
    assert(!(dlist_empty(l)));
    return (l->head->data);
}

void* dlist_access_tail(dlist_t* l){
    assert(!dlist_empty(l));
    return (l->tail->data);
}

/**Retorna o tamanho da dlista**/
size_t dlist_size(dlist_t* l){
    return l->size;
}

/**Retorna verdadeiro se a dlista está vazia, e falso caso contrário**/
size_t dlist_empty(dlist_t* l){
    return dlist_size(l)==0 ? 1 : 0;
}
