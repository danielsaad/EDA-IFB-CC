#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdlib.h>

typedef void *(*generic_queue_node_constructor_fn)(void *);
typedef void (*generic_queue_node_destructor_fn)(void *);

/**A nossa fila consiste de vários nós,
que possuem o tipo generic_queue_node_t **/
typedef struct generic_queue_node_t {
    void *data; /*Ponteiro para um dado genérico de qualquer tipo*/
    struct generic_queue_node_t *next; /*ponteiro para o próximo elemento*/
} generic_queue_node_t;

typedef generic_queue_node_t *generic_queue_iterator_t;

typedef struct generic_queue_t {
    generic_queue_node_t *front; /*Frente da fila*/
    generic_queue_node_t *back;  /*Traseira da fila*/
    generic_queue_node_constructor_fn
        constructor; /*Função para construir o objeto*/
    generic_queue_node_destructor_fn
        destructor; /*Função para destruir o objeto*/
    size_t size;    /*tamanho da fila*/
} generic_queue_t;

/**Inicializa fila**/
void generic_queue_initialize(generic_queue_t **q,
                              generic_queue_node_constructor_fn constructor,
                              generic_queue_node_destructor_fn destructor);
/**Destroi fila**/
void generic_queue_delete(generic_queue_t **q);

/**Retira o elemento da frente da fila**/
void generic_queue_pop(generic_queue_t *q);
/**Insere o elemento na traseira da fila**/
void generic_queue_push(generic_queue_t *q, void *data);
/**Retorna a frente da fila**/
void *generic_queue_front(generic_queue_t *q);

/**Retorna o tamanho da fila**/
size_t generic_queue_size(generic_queue_t *q);
/**Retorna se a fila está vazia ou não**/
size_t generic_queue_empty(generic_queue_t *q);

#endif
