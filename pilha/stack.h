#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdlib.h>

typedef void* (*stack_node_constructor_fn) (void*);
typedef void (*stack_node_destructor_fn)(void *);


/**A nossa pilha consiste de vários nós,
que possuem o tipo stack_node_t **/
typedef struct stack_node_t{
    void* data; /*Ponteiro para um dado genérico de qualquer tipo*/
    struct stack_node_t* next; /*ponteiro para o próximo elemento*/
}stack_node_t;

/**
stack_iterator_t é um apelido para nó da pilha (do tipo stack_node_t). Utilizado quando queremos
iterar na pilha.
 */
typedef stack_node_t* stack_iterator_t;

typedef struct stack_t{
    stack_node_t* top; /*Topo da pilha*/
    stack_node_constructor_fn constructor; /*Função para construir o objeto*/
    stack_node_destructor_fn destructor; /*Função para destruir o objeto*/
    size_t size; /*tamanho da pilha*/
}stack_t;


/**Inicializa pilha**/
void stack_initialize(stack_t** s,stack_node_constructor_fn constructor,
                      stack_node_destructor_fn destructor);
/**Destroi pilha**/
void stack_delete(stack_t** s);

/**Retira o elemento do topo da pilha**/
void stack_pop(stack_t* s);
/**Insere o elemento no topo da pilha**/
void stack_push(stack_t* s,void* data);
/**Retorna o topo da pilha**/
void* stack_top(stack_t* s);

/**Retorna o tamanho da pilha**/
size_t stack_size(stack_t* s);
/**Retorna se a pilha está vazia ou não**/
size_t stack_empty(stack_t* s);
#endif
