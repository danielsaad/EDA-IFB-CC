#include <assert.h>
#include "../Utils/alloc.h"
#include "deque.h"

/**Inicializa o deque**/
void deque_initialize(deque_t** d,deque_node_constructor_fn constructor,
                      deque_node_destructor_fn destructor){
    (*d) = mallocx(sizeof(deque_t));
    (*d)->front = NULL;
    (*d)->back = NULL;
    (*d)->constructor = constructor;
    (*d)->destructor = destructor;
    (*d)->size = 0;
}

/**Deleta o deque**/
void deque_delete(deque_t** d){
    while(!deque_empty(*d)){
        deque_pop_front(*d);
    }
    free(*d);
    (*d) = NULL;
}

/**Insere um elemento no início do deque**/
void deque_push_front(deque_t* d,void* data){
    deque_node_t* new_node = mallocx(sizeof(deque_node_t));
    new_node->data = d->constructor(data);
    new_node->next = d->front;
    new_node->prev = NULL;
    if(deque_empty(d)){
        d->back = new_node;
    }
    else{
        d->front->prev = new_node;
    }
    d->front = new_node;
    d->size++;
}


/**Insere o elemento no final do deque**/
void deque_push_back(deque_t* d,void* data){
    deque_node_t* new_node = mallocx(sizeof(deque_node_t));
    new_node->data = d->constructor(data);
    new_node->next = NULL;
    new_node->prev = d->back;
    if(deque_empty(d)){
        d->front = new_node;
    }
    else{
        d->back->next = new_node;
    }
    d->back = new_node;
    d->size++;
}

/**Retira um elemento do início do deque**/
void deque_pop_front(deque_t* d){
    assert(!deque_empty(d));
    deque_iterator_t it = d->front;
    d->front = d->front->next;
    if(deque_size(d)==1){
        d->back = NULL;
    }
    d->destructor(it->data);
    free(it);
    d->size--;
}

/**Retira um elemento do final do deque**/
void deque_pop_back(deque_t* d){
    assert(!deque_empty(d));
    deque_iterator_t it = d->back;
    d->back = d->back->prev;
    if(deque_size(d)==1){
        d->front = NULL;
    }
    d->destructor(it->data);
    free(it);
    d->size--;
}

/**Retorna o elemento do íncio do deque**/
void* deque_front(deque_t* d){
    assert(!deque_empty(d));
    return(d->front->data);
}

/**Retorna o elemento do final do deque**/
void* deque_back(deque_t* d){
    assert(!deque_empty(d));
    return(d->back->data);
}

/**Retorna o tamanho do deque**/
size_t deque_size(deque_t* d){
    return d->size;
}

/**Retorna se o deque está vazio ou não**/
size_t deque_empty(deque_t* d){
    return deque_size(d) == 0  ? 1 : 0;
}
