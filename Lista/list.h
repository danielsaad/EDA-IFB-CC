#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdlib.h>

typedef void* (*list_node_constructor_fn) (void*);
typedef void (*list_node_destructor_fn)(void *);


/**
  @brief list_node_t Definição de nó de lista ligada.
  O nó de lista ligada contém um ponteiro para um dado genérico (data)
  e um ponteiro para o próximo nó da lista.
**/
typedef struct list_node_t{
    void* data; /*Ponteiro para um dado genérico de qualquer tipo*/
    struct list_node_t* next; /*ponteiro para o próximo elemento*/
}list_node_t;


/**
 * @brief list_iterator_t Tipo para iterar na lista ligada.
 * O list_iterator_t é apenas um apelido para list_node_t*. Ele é utilizado
 * no código quando o propósito é andar na lista. Deixa o código mais claro,
 * pois quando declarado indica explicitamente a intenção da variável.
 */
typedef list_node_t* list_iterator_t;

typedef struct list_t{
    list_node_t* head; /*Cabeça da Lista*/
    list_node_t* tail; /*Cauda da Lista*/
    list_node_constructor_fn constructor; /*Função para construir o objeto*/
    list_node_destructor_fn destructor; /*Função para destruir o objeto*/
    size_t size; /*tamanho da lista*/
}list_t;


/**
 * @brief list_initialize Inicializa uma lista ligada.
 * @param l Ponteiro de ponteiro para tipo lista.
 * @param constructor Função construtora.
 * @param destructor Função destrutora.
 * Esta função é responsável por alocar dinâmicamente as variáveis do tipo
 * lista e atribuir as funções construtoras e destrutoras a esta lista.
 * No caso l é passado como 'referência'.
 */
void list_initialize(list_t** l,list_node_constructor_fn constructor,
	list_node_destructor_fn destructor);
/**
 * @brief list_delete Deleta a lista e todos os seus elementos.
 * @param l Lista
 * Deleta a lista e todos os seus elementos ao aplicar o destrutor em cada
 * nó da lista e desalocar a lista.
 */
void list_delete(list_t** l);

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
void list_insert(list_t* l,void* data,size_t i);

/**
 * @brief list_prepend Insere um elemento na cabeça da lista.
 * @param l Lista encadeada.
 * @param data Dado a ser inserido.
 */
void list_prepend(list_t* l,void* data);

/**
 * @brief list_append Insere um elemento na cauda da lista.
 * @param l lista encadeada.
 * @param data Dado a ser inserido.
 */
void list_append(list_t* l, void* data);

/**
 * @brief list_remove Remove um elemento da lista em uma posição específica.
 * @param l Lista encadeada.
 * @param i Posição do nó da lista a ser removido.
 * Remove um elemento da lista em uma posição específica. Se i==0, a remoção
 * é feita na cabeça. Se i==n-1, onde n é o tamanho da lista, a remoção é feita
 * na cauda. Caso contrário, o elemento da posição i é removido.
 */
void list_remove(list_t* l,size_t i);


/**
 * @brief list_remove_head Removea cabeça da lista.
 * @param l Lista encadeada.
 */
void list_remove_head(list_t* l);

/**
 * @brief list_remove_tail Remove a cauda da
 * @param l Lista encadeada.
 */

/**
 * @brief list_remove_tail Remove a cauda da lista.
 * @param l Lista encadeada.
 */
void list_remove_tail(list_t* l);

/**
 * @brief list_access Acessa o elemento de uma posição específica da lista.
 * @param l Lista encadeada.
 * @param i Posição a ser acessada.
 * @return O dado que ocupa a i-ésima posição.
 * Se i==0, então o elemento da cabeça é acessado. Se i==n-1, onde n é o tamanho
 * da lista, o elemento acessado é o da cauda.
 */
void* list_access(list_t* l,size_t i);

/**
 * @brief list_access_head Acessa a cabeça da lista.
 * @param l Lista encadeada.
 * @return O dado contido na cabeça da lista.
 */
void* list_access_head(list_t* l);

/**
 * @brief list_access_tail Acessa a cauda da lista
 * @param l Lista encadeada.
 * @return Retorna o dado contido na cauda da lista.
 */
void* list_access_tail(list_t* l);

/**
 * @brief list_size Indica o tamanho da lista.
 * @param l Lista encadeada.
 * @return O tamanho da lista.
 */
size_t list_size(list_t* l);

/**
 * @brief list_empty Verifica se a lista está vazia;
 * @param l Lista encadeada.
 * @return Verdadeiro(1) se a lista está vazia, e falso(0) caso contrário
 */
size_t list_empty(list_t* l);


#endif // LIST_H_INCLUDED
