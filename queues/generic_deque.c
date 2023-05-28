#include <assert.h>
#include "../utils/alloc.h"
#include "generic_deque.h"

/**Inicializa o generic_deque**/
void generic_deque_initialize(generic_deque_t** d,generic_deque_node_constructor_fn constructor,
                      generic_deque_node_destructor_fn destructor){
    (*d) = mallocx(sizeof(generic_deque_t));
    (*d)->front = NULL;
    (*d)->back = NULL;
    (*d)->constructor = constructor;
    (*d)->destructor = destructor;
    (*d)->size = 0;
}

/**Deleta o generic_deque**/
void generic_deque_delete(generic_deque_t** d){
    while(!generic_deque_empty(*d)){
        generic_deque_pop_front(*d);
    }
    free(*d);
    (*d) = NULL;
}

/**Insere um elemento no início do generic_deque**/
void generic_deque_push_front(generic_deque_t* d,void* data){
    generic_deque_node_t* new_node = mallocx(sizeof(generic_deque_node_t));
    new_node->data = d->constructor(data);
    new_node->next = d->front;
    new_node->prev = NULL;
    if(generic_deque_empty(d)){
        d->back = new_node;
    }
    else{
        d->front->prev = new_node;
    }
    d->front = new_node;
    d->size++;
}


/**Insere o elemento no final do generic_deque**/
void generic_deque_push_back(generic_deque_t* d,void* data){
    generic_deque_node_t* new_node = mallocx(sizeof(generic_deque_node_t));
    new_node->data = d->constructor(data);
    new_node->next = NULL;
    new_node->prev = d->back;
    if(generic_deque_empty(d)){
        d->front = new_node;
    }
    else{
        d->back->next = new_node;
    }
    d->back = new_node;
    d->size++;
}

/**Retira um elemento do início do generic_deque**/
void generic_deque_pop_front(generic_deque_t* d){
    assert(!generic_deque_empty(d));
    generic_deque_iterator_t it = d->front;
    d->front = d->front->next;
    if(generic_deque_size(d)==1){
        d->back = NULL;
    }
    else{
        d->front->prev = NULL;
    }
    d->destructor(it->data);
    free(it);
    d->size--;
}

/**Retira um elemento do final do generic_deque**/
void generic_deque_pop_back(generic_deque_t* d){
    assert(!generic_deque_empty(d));
    generic_deque_iterator_t it = d->back;
    d->back = d->back->prev;
    if(generic_deque_size(d)==1){
        d->front = NULL;
    }
    else{
        d->back->next = NULL;
    }
    d->destructor(it->data);
    free(it);
    d->size--;
}

/**Retorna o elemento do íncio do generic_deque**/
void* generic_deque_front(generic_deque_t* d){
    assert(!generic_deque_empty(d));
    return(d->front->data);
}

/**Retorna o elemento do final do generic_deque**/
void* generic_deque_back(generic_deque_t* d){
    assert(!generic_deque_empty(d));
    return(d->back->data);
}

/**Retorna o tamanho do generic_deque**/
size_t generic_deque_size(generic_deque_t* d){
    return d->size;
}

/**Retorna se o generic_deque está vazio ou não**/
size_t generic_deque_empty(generic_deque_t* d){
    return generic_deque_size(d) == 0  ? 1 : 0;
}
