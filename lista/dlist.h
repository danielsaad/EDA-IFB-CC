#ifndef DLIST_H_INCLUDED
#define DLIST_H_INCLUDED

#include <stdbool.h>
#include <stdlib.h>

/**A nossa dlista encadeada consiste de vários nós,
que possuem o tipo dlist_node_t **/
typedef struct dlist_node_t {
    int data;                  /*Dado*/
    struct dlist_node_t *next; /*ponteiro para o próximo elemento*/
    struct dlist_node_t *prev; /*Ponteiro para o elemento anterior*/
} dlist_node_t;

typedef struct dlist_t {
    dlist_node_t *head; /*Cabeça da dlista*/
    dlist_node_t *tail; /*Cauda da dlista*/
    size_t size;        /*tamanho da dlista*/
} dlist_t;

/** Protótipos **/

/**Operações na dlista**/
/**Inicializa a dlista**/
void dlist_initialize(dlist_t **l);
/**Deleta a dlista**/
void dlist_delete(dlist_t **l);
/**Insere um elemento na dlista na posição i**/
void dlist_insert(dlist_t *l, int data, size_t i);
/**Anexa um elemento na cabeça da dlista**/
void dlist_prepend(dlist_t *l, int data);
/**Anexa um elemento na cauda da dlista**/
void dlist_append(dlist_t *l, int data);
/**Remove o elemento da posição i da dlista**/
void dlist_remove(dlist_t *l, size_t i);
/**Remove a cabeça da dlista**/
void dlist_remove_head(dlist_t *l);
/**Remove a cauda da dlista**/
void dlist_remove_tail(dlist_t *l);
/**Acessa o conteúdo da dlista na posição i**/
int dlist_access(dlist_t *l, size_t i);
/**Acessa o conteúdo da cabeça**/
int dlist_access_head(dlist_t *l);
/**Acessa o conteúdo da cauda**/
int dlist_access_tail(dlist_t *l);
/**Retorna o tamanho da dlista**/
size_t dlist_size(dlist_t *l);
/**Retorna se a dlista está vazia ou não**/
bool dlist_empty(dlist_t *l);

#endif // DLIST_H_INCLUDED
