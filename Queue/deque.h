#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

#include <stdlib.h>

typedef void* (*deque_node_constructor_fn) (void*);
typedef void (*deque_node_destructor_fn)(void *);

typedef struct deque_node_t{
    struct deque_node_t* next;
    struct deque_node_t* prev;
    void* data;
}deque_node_t;

typedef deque_node_t* deque_iterator_t;

typedef struct deque_t{
    struct deque_node_t* front;
    struct deque_node_t* back;
    deque_node_constructor_fn constructor;
    deque_node_destructor_fn destructor;
    size_t size;
}deque_t;

/**Inicializa o deque**/
void initialize_deque(deque_t** d,deque_node_constructor_fn constructor,
                      deque_node_destructor_fn destructor);
/**Deleta o deque**/
void delete_deque(deque_t** d);
/**Insere um elemento no início do deque**/
void deque_push_front(deque_t* d,void* data);
/**Insere o elemento no final do deque**/
void deque_push_back(deque_t* d,void* data);
/**Retira um elemento do início do deque**/
void deque_pop_front(deque_t* d);
/**Retira um elemento do final do deque**/
void deque_pop_back(deque_t* d);
/**Retorna o elemento do íncio do deque**/
void* deque_front(deque_t* d);
/**Retorna o elemento do final do deque**/
void* deque_back(deque_t* d);
/**Retorna o tamanho do deque**/
size_t deque_size(deque_t* d);
/**Retorna se o deque está vazio ou não**/
size_t deque_empty(deque_t* d);


#endif
