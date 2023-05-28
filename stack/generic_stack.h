#ifndef GENERIC_STACK_H_INCLUDED
#define GENERIC_STACK_H_INCLUDED

#include <stdlib.h>

typedef void* (*generic_stack_node_constructor_fn) (void*);
typedef void (*generic_stack_node_destructor_fn)(void *);


/**A nossa pilha consiste de vários nós,
que possuem o tipo generic_stack_node_t **/
typedef struct generic_stack_node_t{
    void* data; /*Ponteiro para um dado genérico de qualquer tipo*/
    struct generic_stack_node_t* next; /*ponteiro para o próximo elemento*/
}generic_stack_node_t;

/**
generic_stack_iterator_t é um apelido para nó da pilha (do tipo generic_stack_node_t). Utilizado quando queremos
iterar na pilha.
 */
typedef generic_stack_node_t* generic_stack_iterator_t;

typedef struct generic_stack_t{
    generic_stack_node_t* top; /*Topo da pilha*/
    generic_stack_node_constructor_fn constructor; /*Função para construir o objeto*/
    generic_stack_node_destructor_fn destructor; /*Função para destruir o objeto*/
    size_t size; /*tamanho da pilha*/
}generic_stack_t;


/**Inicializa pilha**/
void generic_stack_initialize(generic_stack_t** s,generic_stack_node_constructor_fn constructor,
                      generic_stack_node_destructor_fn destructor);
/**Destroi pilha**/
void generic_stack_delete(generic_stack_t** s);

/**Retira o elemento do topo da pilha**/
void generic_stack_pop(generic_stack_t* s);
/**Insere o elemento no topo da pilha**/
void generic_stack_push(generic_stack_t* s,void* data);
/**Retorna o topo da pilha**/
void* generic_stack_top(generic_stack_t* s);

/**Retorna o tamanho da pilha**/
size_t generic_stack_size(generic_stack_t* s);
/**Retorna se a pilha está vazia ou não**/
size_t generic_stack_empty(generic_stack_t* s);
#endif
