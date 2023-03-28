#include <assert.h>
#include "dlist.h"
#include "../Utils/alloc.h"

static dlist_node_t* dlist_new_node(void* data,dlist_node_constructor_fn constructor);
static void dlist_delete_node(dlist_node_t* node,dlist_node_destructor_fn destructor);

static dlist_node_t* dlist_new_node(void* data,dlist_node_constructor_fn constructor){
    dlist_node_t* new_node =  mallocx(sizeof(dlist_node_t));
    new_node->data = constructor(data);
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}


static void dlist_delete_node(dlist_node_t* node,dlist_node_destructor_fn destructor){
    destructor(node->data);
    free(node);
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
/** Deleta a lista por inteiro e libera espaço em memória **/
void dlist_delete(dlist_t** l){
    while(!dlist_empty(*l)){
        dlist_remove_head(*l);
    }
    free(*l);
    *l = NULL;
}

void dlist_insert(dlist_t* l,void* data,size_t i){
    assert(i<=dlist_size(l));
    if(dlist_empty(l) || i==0){
		dlist_prepend(l,data);
	}
    else if(i==dlist_size(l)){
        /*Inserção na cauda*/
		dlist_append(l,data);
    }
    else{
		dlist_node_t* new_node = dlist_new_node(data,l->constructor);
        /*Inserção no meio da lista*/
        /*Precisamos encontrar o elemento que antecede a posição i*/
        dlist_iterator_t it = l->head;
        size_t k;
        for(k=0;k<i-1;k++){
            it = it->next;
        }
        /*aux agora aponta pro elemento da posição i-1*/
        new_node->next = it->next;
        new_node->prev = it;
        it->next->prev = new_node;
        it->next = new_node;
		l->size++;
    }
}

/** Insere um elemento na cabeça da dlista **/
void dlist_prepend(dlist_t* l,void* data){
    dlist_node_t* new_node = dlist_new_node(data,l->constructor);
    if(dlist_empty(l)){
        l->tail = new_node;
    }
    else{
        l->head->prev = new_node;
    }
    new_node->next = l->head;
    l->head = new_node;
    l->size++;
}

/**Insere um elemento na cauda da dlista **/
void dlist_append(dlist_t* l, void* data){
    dlist_node_t* new_node = dlist_new_node(data,l->constructor);
    if(dlist_empty(l)){
        l->head = new_node;
    }
    else{
        l->tail->next = new_node;
    }
    new_node->prev = l->tail;
    l->tail = new_node;
    l->size++;
}

/**Remove o elemento da posição i da dlista**/
void dlist_remove(dlist_t* l,size_t i){
    assert(!dlist_empty(l) && i<dlist_size(l));
    dlist_node_t* node;
    if(dlist_size(l)==1 || i==0){
		dlist_remove_head(l);
	}
    else if(i==dlist_size(l)-1){
        dlist_remove_tail(l);
    }
    else{
        dlist_iterator_t it = l->head;
        size_t k;
        for(k=0;k<i;k++){
            it = it->next;
        }
        node = it;
        node->prev->next = node->next;
        node->next->prev = node->prev;
		dlist_delete_node(node,l->destructor);
		l->size--;
    }

}

void dlist_remove_head(dlist_t* l){
    assert(!dlist_empty(l));
    dlist_iterator_t node = l->head;
    l->head = l->head->next;
    if(dlist_size(l)==1){
        l->tail = NULL;
    }
    else{
        l->head->prev = NULL;
    }
    dlist_delete_node(node,l->destructor);
    l->size--;
}

void dlist_remove_tail(dlist_t* l){
    assert(!dlist_empty(l));
    dlist_iterator_t node = l->tail;
    l->tail = l->tail->prev;
    if(dlist_size(l)==1){
        l->head = NULL;
    }
    else{
        l->tail->next = NULL;
    }
    dlist_delete_node(node,l->destructor);
    l->size--;
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
