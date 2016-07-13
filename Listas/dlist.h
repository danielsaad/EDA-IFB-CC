#ifndef dlist_H_INCLUDED
#define dlist_H_INCLUDED

#include <stdlib.h>

typedef void* (*dlist_node_constructor_fn) (void*);
typedef void (*dlist_node_destructor_fn)(void *);


/**A nossa dlista encadeada consiste de vários nós,
que possuem o tipo linked_dlist_node_t **/
typedef struct dlist_node_t{
    void* data; /*Ponteiro para um dado genérico de qualquer tipo*/
    struct dlist_node_t* next; /*ponteiro para o próximo elemento*/
    struct dlist_node_t* prev; /*Ponteiro para o elemento anterior*/
}dlist_node_t;


typedef dlist_node_t* ddlist_iterator_t;

typedef struct ddlist_t{
    dlist_node_t* head; /*Cabeça da dlista*/
    dlist_node_t* tail; /*Cauda da dlista*/
    dlist_node_constructor_fn constructor; /*Função para construir o objeto*/
    dlist_node_destructor_fn destructor; /*Função para destruir o objeto*/
    size_t size; /*tamanho da dlista*/
}dlist_t;


/** Protótipos **/

/**Operações nos nós**/
/**Cria um novo nó**/
dlist_node_t* ddlist_node_new(void* data,ddlist_node_constructor_fn constructor);

/**Operações na dlista**/
/**Inicializa a dlista**/
void dlist_initialize(dlist_t** l,dlist_node_constructor_fn constructor,
    dlist_node_destructor_fn destructor);
/**Deleta a dlista**/
void dlist_delete(dlist_t** l);
/**Insere um elemento na dlista na posição i**/
void dlist_insert(dlist_t* l,void* data,int i);
/**Anexa um elemento na cabeça da dlista**/
void dlist_prepend(dlist_t* l,void* data);
/**Anexa um elemento na cauda da dlista**/
void dlist_append(dlist_t* l, void* data);
/**Remove o elemento da posição i da dlista**/
void dlist_remove(dlist_t* l,int i);
/**Remove a cabeça da dlista**/
void dlist_remove_head(dlist_t* l);
/**Remove a cauda da dlista**/
void dlist_remove_tail(dlist_t* l);
/**Acessa o conteúdo da dlista na posição i**/
void* dlist_access(dlist_t* l,int i);
/**Acessa o conteúdo da cabeça**/
void* dlist_access_head(dlist_t* l);
/**Acessa o conteúdo da cauda**/
void* dlist_access_tail(dlist_t* l);
/**Retorna o tamanho da dlista**/
size_t dlist_size(dlist_t* l);
/**Retorna se a dlista está vazia ou não**/
size_t dlist_empty(dlist_t* l);

/*Operações sobre iterators*/
void* dlist_iterator_data(dlist_iterator_t it);

#endif // dlist_H_INCLUDED
