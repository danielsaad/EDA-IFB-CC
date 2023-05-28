#ifndef GENERIC_LIST_H_INCLUDED
#define GENERIC_LIST_H_INCLUDED

#include <stdbool.h>
#include <stdlib.h>

typedef void *(*generic_list_node_constructor_fn)(void *);
typedef void (*generic_list_node_destructor_fn)(void *);

/**
  @brief generic_list_node_t Definição de nó de lista ligada.
  O nó de lista ligada contém um ponteiro para um dado genérico (data)
  e um ponteiro para o próximo nó da lista.
**/
typedef struct generic_list_node_t {
    void *data; /*Ponteiro para um dado genérico de qualquer tipo*/
    struct generic_list_node_t *next; /*ponteiro para o próximo elemento*/
} generic_list_node_t;

/**
 * @brief generic_list_iterator_t Tipo para iterar na lista ligada.
 * O generic_list_iterator_t é apenas um apelido para generic_list_node_t*. Ele
 * é utilizado no código quando o propósito é andar na lista. Deixa o código
 * mais claro, pois quando declarado indica explicitamente a intenção da
 * variável.
 */
typedef generic_list_node_t *generic_list_iterator_t;

/**
  @brief generic_list_t Definidção do tipo lista. Contém ponteiros para a cabeça
e cauda da lista, as funções construtoras e destrutoras dos elementos das listas
e o tamanho da lista.
**/
typedef struct generic_list_t {
    generic_list_node_t *head; /*Cabeça da Lista*/
    generic_list_node_t *tail; /*Cauda da Lista*/
    generic_list_node_constructor_fn
        constructor; /*Função para construir o objeto*/
    generic_list_node_destructor_fn
        destructor; /*Função para destruir o objeto*/
    size_t size;    /*tamanho da lista*/
} generic_list_t;

/**
 * @brief list_initialize Inicializa uma lista ligada.
 * @param l Ponteiro de ponteiro para tipo lista.
 * @param constructor Função construtora.
 * @param destructor Função destrutora.
 * Esta função é responsável por alocar dinâmicamente as variáveis do tipo
 * lista e atribuir as funções construtoras e destrutoras a esta lista.
 * No caso l é passado como 'referência'.
 */
void generic_list_initialize(generic_list_t **l,
                     generic_list_node_constructor_fn constructor,
                     generic_list_node_destructor_fn destructor);
/**
 * @brief list_delete Deleta a lista e todos os seus elementos.
 * @param l Lista
 * Deleta a lista e todos os seus elementos ao aplicar o destrutor em cada
 * nó da lista e desalocar a lista.
 */
void generic_list_delete(generic_list_t **l);

/**
 * @brief list_insert Insere um elemento na lista em uma posição especificada.
 * @param l Lista encadeada.
 * @param data Dado a ser inserido.
 * @param i Posição na qual o dado será inserido.
 * Insere um dado em uma posição árbitrária da lista. Se i==0, a inserção
 * é feita na cabeça. Se i==n, onde n é o tamanho da lista, a inserção é feita
 * na cauda. Caso contrário, o dado é inserido entre as posições (i-1) e (i)
 * da lista original.
 */
void generic_list_insert(generic_list_t *l, void *data, size_t i);

/**
 * @brief list_prepend Insere um elemento na cabeça da lista.
 * @param l Lista encadeada.
 * @param data Dado a ser inserido.
 */
void generic_list_prepend(generic_list_t *l, void *data);

/**
 * @brief list_append Insere um elemento na cauda da lista.
 * @param l lista encadeada.
 * @param data Dado a ser inserido.
 */
void generic_list_append(generic_list_t *l, void *data);

/**
 * @brief list_remove Remove um elemento da lista em uma posição específica.
 * @param l Lista encadeada.
 * @param i Posição do nó da lista a ser removido.
 * Remove um elemento da lista em uma posição específica. Se i==0, a remoção
 * é feita na cabeça. Se i==n-1, onde n é o tamanho da lista, a remoção é feita
 * na cauda. Caso contrário, o elemento da posição i é removido.
 */
void generic_list_remove(generic_list_t *l, size_t i);

/**
 * @brief list_remove_head Removea cabeça da lista.
 * @param l Lista encadeada.
 */
void generic_list_remove_head(generic_list_t *l);

/**
 * @brief list_remove_tail Remove a cauda da
 * @param l Lista encadeada.
 */

/**
 * @brief list_remove_tail Remove a cauda da lista.
 * @param l Lista encadeada.
 */
void generic_list_remove_tail(generic_list_t *l);

/**
 * @brief list_access Acessa o elemento de uma posição específica da lista.
 * @param l Lista encadeada.
 * @param i Posição a ser acessada.
 * @return O dado que ocupa a i-ésima posição.
 * Se i==0, então o elemento da cabeça é acessado. Se i==n-1, onde n é o tamanho
 * da lista, o elemento acessado é o da cauda.
 */
void *generic_list_access(generic_list_t *l, size_t i);

/**
 * @brief list_access_head Acessa a cabeça da lista.
 * @param l Lista encadeada.
 * @return O dado contido na cabeça da lista.
 */
void *generic_list_access_head(generic_list_t *l);

/**
 * @brief list_access_tail Acessa a cauda da lista
 * @param l Lista encadeada.
 * @return Retorna o dado contido na cauda da lista.
 */
void *generic_list_access_tail(generic_list_t *l);

/**
 * @brief list_size Indica o tamanho da lista.
 * @param l Lista encadeada.
 * @return O tamanho da lista.
 */
size_t generic_list_size(generic_list_t *l);

/**
 * @brief list_empty Verifica se a lista está vazia;
 * @param l Lista encadeada.
 * @return Verdadeiro(1) se a lista está vazia, e falso(0) caso contrário
 */
bool generic_list_empty(generic_list_t *l);

#endif // LIST_H_INCLUDED
