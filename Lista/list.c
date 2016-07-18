#include <assert.h>
#include "list.h"
#include "../Utils/alloc.h"

static list_node_t* list_new_node(void* data,list_node_constructor_fn constructor);

static list_node_t* list_new_node(void* data,list_node_constructor_fn constructor){
    list_node_t* new_node =  mallocx(sizeof(list_node_t));
    new_node->data = constructor(data);
    new_node->next = NULL;
    return new_node;
}

/**Inicializa a Lista e seus membros**/
void list_initialize(list_t** l,list_node_constructor_fn constructor,
    list_node_destructor_fn destructor){
    (*l) = mallocx(sizeof(list_t));
    (*l)->head = NULL;
    (*l)->tail = NULL;
    (*l)->size = 0;
    (*l)->constructor = constructor;
    (*l)->destructor = destructor;
}

void list_delete(list_t** l){
    while(!list_empty(*l)){
        list_remove_head(*l);
    }
    free(*l);
    *l = NULL;
}

void list_insert(list_t* l,void* data,size_t i){
    assert(i<=list_size(l));
    list_node_t* new_node = list_new_node(data,l->constructor);
    if(list_empty(l)){
        /*Se a lista está vazia, cabeça e cauda apontam para o mesmo lugar*/
        l->head = new_node;
        l->tail = new_node;
    }
    else if(i==0){
        /*Inserção na cabeça*/
        new_node->next = l->head;
        l->head = new_node;
    }
    else if(i==list_size(l)){
        /*Inserção na cauda*/
        l->tail = new_node;
    }
    else{
        /*Inserção no meio da lista*/
        /*Precisamos encontrar o elemento que antecede a posição i*/
        list_iterator_t it = l->head;
        int k;
        for(k=0;k<i-1;k++){
            it = it->next;
        }
        /*aux agora aponta pro elemento da posição i-1*/
        new_node->next = it->next;
        it->next = new_node;
    }
    l->size++;
}

/** Insere um elemento na cabeça da lista **/
void list_prepend(list_t* l,void* data){
    list_node_t* new_node = list_new_node(data,l->constructor);
    new_node->next = l->head;
    l->head = new_node;
    if(list_empty(l)){
        l->tail = new_node;
    }
    l->size++;
}

/**Insere um elemento na cauda da lista **/
void list_append(list_t* l, void* data){
    list_node_t* new_node = list_new_node(data,l->constructor);
    if(list_empty(l)){
        l->head = new_node;
    }
    else{
        l->tail->next = new_node;
    }
    l->tail = new_node;
    l->size++;
}

/**Remove o elemento da posição i da lista**/
void list_remove(list_t* l,size_t i){
    assert(!list_empty(l) && i<list_size(l));
    list_node_t* node;
    if(list_size(l)==1){
        /*Remoção em uma lista com um elemento*/
        node = l->head;
        l->head = NULL;
        l->tail = NULL;
    }
    else if(i==0){
        /*Remoção na cabeça*/
        node = l->head;
        l->head = l->head->next;
    }
    else if(i==list_size(l)-1){
        node = l->tail;
        list_iterator_t it = l->head;
        while(it->next!=NULL){
            it = it->next;
        }
        l->tail = it;
        l->tail->next = NULL;
    }
    else{
        list_iterator_t it = l->head;
        int k;
        for(k=0;k<i-1;k++){
            it = it->next;
        }
        node = it->next;
        it->next = node->next;
    }
    l->destructor(node->data);
    free(node);
    l->size--;

}

void list_remove_head(list_t* l){
    assert(!list_empty(l));
    list_iterator_t it = l->head;
    if(list_size(l)==1){
        l->head = NULL;
        l->tail = NULL;
    }
    else{
        l->head = l->head->next;
    }
    l->destructor(it->data);
    free(it);
}

void list_remove_tail(list_t* l){
    assert(list_size(l)>0);
    if(list_size(l)==1){
        l->destructor(l->tail->data);
        free(l->tail);
        l->head = NULL;
        l->tail = NULL;
    }
    else{
        list_iterator_t it = l->head;
        while(it->next!=NULL){
            it = it->next;
        }
        it->next = NULL;
        l->destructor(l->tail->data);
        free(l->tail);
        l->tail = it;
    }
}

void* list_access(list_t* l,size_t i){
    assert(list_size(l)>0 && i<list_size(l));
    list_iterator_t it = l->head;
    int j;
    for(j=0;j<i-1;j++){
        it = it->next;
    }
    return(it->data);
}

void* list_access_head(list_t* l){
    assert(!(list_empty(l)));
    return (l->head->data);
}

void* list_access_tail(list_t* l){
    assert(!list_empty(l));
    return (l->tail->data);
}

/**Retorna o tamanho da lista**/
size_t list_size(list_t* l){
    return l->size;
}

/**Retorna verdadeiro se a lista está vazia, e falso caso contrário**/
size_t list_empty(list_t* l){
    return list_size(l)==0 ? 1 : 0;
}
