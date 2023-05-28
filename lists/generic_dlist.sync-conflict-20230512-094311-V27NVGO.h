#ifndef GENERIC_DLIST_H_INCLUDED
#define GENERIC_DLIST_H_INCLUDED

#include <stdlib.h>

typedef void* (*generic_dlist_node_constructor_fn) (void*);
typedef void (*generic_dlist_node_destructor_fn)(void *);


/**A nossa generic_dlista encadeada consiste de vários nós,
que possuem o tipo linked_generic_dlist_node_t **/
typedef struct generic_dlist_node_t{
    void* data; /*Ponteiro para um dado genérico de qualquer tipo*/
    struct generic_dlist_node_t* next; /*ponteiro para o próximo elemento*/
    struct generic_dlist_node_t* prev; /*Ponteiro para o elemento anterior*/
}generic_dlist_node_t;


typedef generic_dlist_node_t* generic_dlist_iterator_t;

typedef struct generic_dlist_t{
    generic_dlist_node_t* head; /*Cabeça da generic_dlista*/
    generic_dlist_node_t* tail; /*Cauda da generic_dlista*/
    generic_dlist_node_constructor_fn constructor; /*Função para construir o objeto*/
    generic_dlist_node_destructor_fn destructor; /*Função para destruir o objeto*/
    size_t size; /*tamanho da generic_dlista*/
}generic_dlist_t;


/** Protótipos **/

/**Operações na generic_dlista**/
/**Inicializa a generic_dlista**/
void generic_dlist_initialize(generic_dlist_t** l,generic_dlist_node_constructor_fn constructor,
    generic_dlist_node_destructor_fn destructor);
/**Deleta a generic_dlista**/
void generic_dlist_delete(generic_dlist_t** l);
/**Insere um elemento na generic_dlista na posição i**/
void generic_dlist_insert(generic_dlist_t* l,void* data,size_t i);
/**Anexa um elemento na cabeça da generic_dlista**/
void generic_dlist_prepend(generic_dlist_t* l,void* data);
/**Anexa um elemento na cauda da generic_dlista**/
void generic_dlist_append(generic_dlist_t* l, void* data);
/**Remove o elemento da posição i da generic_dlista**/
void generic_dlist_remove(generic_dlist_t* l,size_t i);
/**Remove a cabeça da generic_dlista**/
void generic_dlist_remove_head(generic_dlist_t* l);
/**Remove a cauda da generic_dlista**/
void generic_dlist_remove_tail(generic_dlist_t* l);
/**Acessa o conteúdo da generic_dlista na posição i**/
void* generic_dlist_access(generic_dlist_t* l,size_t i);
/**Acessa o conteúdo da cabeça**/
void* generic_dlist_access_head(generic_dlist_t* l);
/**Acessa o conteúdo da cauda**/
void* generic_dlist_access_tail(generic_dlist_t* l);
/**Retorna o tamanho da generic_dlista**/
size_t generic_dlist_size(generic_dlist_t* l);
/**Retorna se a generic_dlista está vazia ou não**/
size_t generic_dlist_empty(generic_dlist_t* l);

/*Operações sobre iterators*/
void* generic_dlist_iterator_data(generic_dlist_iterator_t it);

#endif // generic_dlist_H_INCLUDED
