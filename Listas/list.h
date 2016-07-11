#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdlib.h>

typedef void* (*list_node_constructor_fn) (void*);
typedef void (*list_node_destructor_fn)(void *);


/**A nossa lista encadeada consiste de vários nós,
que possuem o tipo linked_list_node_t **/
typedef struct list_node_t{
    void* data; /*Ponteiro para um dado genérico de qualquer tipo*/
    struct list_node_t* next; /*ponteiro para o próximo elemento*/
}list_node_t;

typedef list_node_t* list_iterator;


typedef struct linked_list_t{
    list_node_t* head; /*Cabeça da Lista*/
    list_node_t* tail; /*Cauda da Lista*/
    list_node_constructor_fn constructor; /*Função para construir o objeto*/
    list_node_destructor_fn destructor; /*Função para destruir o objeto*/
    size_t size; /*tamanho da lista*/
}list_t;


/** Protótipos **/

/**Operações nos nós**/
/**Cria um novo nó**/
list_node_t* list_node_new(void* data,list_node_constructor_fn constructor);

/**Operações na lista**/
/**Inicializa a lista**/
void list_initialize(list_t** l,list_node_constructor_fn constructor,
	list_node_destructor_fn destructor);
/**Deleta a lista**/
void list_delete(list_t** l);
/**Insere um elemento na lista na posição i**/
void list_insert(list_t* l,void* data,int i);
/**Anexa um elemento na cabeça da lista**/
void list_prepend(list_t* l,void* data);
/**Anexa um elemento na cauda da lista**/
void list_append(list_t* l, void* data);
/**Remove o elemento da posição i da lista**/
void list_remove(list_t* l,int i);
/**Remove a cabeça da lista**/
void list_remove_head(list_t* l);
/**Remove a cauda da lista**/
void list_remove_tail(list_t* l);
/**Acessa o conteúdo da lista na posição i**/
void* list_access(list_t* l,int i);
/**Acessa o conteúdo da cabeça**/
void* list_access_head(list_t* l);
/**Acessa o conteúdo da cauda**/
void* list_access_tail(list_t* l);
/**Retorna o tamanho da lista**/
size_t list_size(list_t* l);
/**Retorna se a lista está vazia ou não**/
size_t list_empty(list_t* l);

/*Operações sobre iterators*/
void* list_iterator_data(list_iterator it);

#endif // LIST_H_INCLUDED
