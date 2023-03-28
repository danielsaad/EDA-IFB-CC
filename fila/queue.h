#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdlib.h>

typedef void* (*queue_node_constructor_fn) (void*);
typedef void (*queue_node_destructor_fn)(void *);


/**A nossa fila consiste de vários nós,
que possuem o tipo queue_node_t **/
typedef struct queue_node_t{
    void* data; /*Ponteiro para um dado genérico de qualquer tipo*/
    struct queue_node_t* next; /*ponteiro para o próximo elemento*/
}queue_node_t;

typedef queue_node_t* queue_iterator_t;

typedef struct queue_t{
    queue_node_t* front; /*Frente da fila*/
    queue_node_t* back; /*Traseira da fila*/
    queue_node_constructor_fn constructor; /*Função para construir o objeto*/
    queue_node_destructor_fn destructor; /*Função para destruir o objeto*/
    size_t size; /*tamanho da fila*/
}queue_t;


/**Inicializa fila**/
void queue_initialize(queue_t** q,queue_node_constructor_fn constructor,
                      queue_node_destructor_fn destructor);
/**Destroi fila**/
void queue_delete(queue_t** q);

/**Retira o elemento da frente da fila**/
void queue_pop(queue_t* q);
/**Insere o elemento na traseira da fila**/
void queue_push(queue_t* q,void* data);
/**Retorna a frente da fila**/
void* queue_front(queue_t* q);

/**Retorna o tamanho da fila**/
size_t queue_size(queue_t* q);
/**Retorna se a fila está vazia ou não**/
size_t queue_empty(queue_t* q);

#endif
