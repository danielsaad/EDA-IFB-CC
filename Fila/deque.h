#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

#include <stdlib.h>

/**
 * @brief Definição do tipo construtor: um ponteiro para função que retorna
 * o objeto alocado e recbe o objeto a ser copiado.
 */
typedef void* (*deque_node_constructor_fn) (void*);


/**
 * @brief Definição do tipo destrutor: um ponteiro para função que não retorna
 * nada e recebe o dado a ser destruído.
 */
typedef void (*deque_node_destructor_fn)(void *);


/**
 * @brief deque_node_t Definição do nó do deque.
 * Possui um ponteiro para o dado genérico alocado pelo construtor,
 * um ponteiro para o próximo elemento e um elemento para o próximo.
 * O deque é implementado através da estrutura list duplamento encadeada.
 */


typedef struct deque_node_t{
    struct deque_node_t* next;
    struct deque_node_t* prev;
    void* data;
}deque_node_t;

/**
 * @brief deque_iterator_t Apelido para nó do deque. Utilizado quando queremos
 * iterar no deque.
 */
typedef deque_node_t* deque_iterator_t;


/**
 * @brief deque_t Tipo deque. Possui ponteiros para frente, final e ponteiros
 * para as funções construtora, destrutora. O tamanho do deque também está
 * presente.
 */
typedef struct deque_t{
    struct deque_node_t* front;
    struct deque_node_t* back;
    deque_node_constructor_fn constructor;
    deque_node_destructor_fn destructor;
    size_t size;
}deque_t;


/**
 * @brief deque_initialize Inicializa a estrutura deque.
 * @param d Ponteiro para estrutura deque.
 * @param constructor Função construtora.
 * @param destructor Função destrutora.
 */
void deque_initialize(deque_t** d,deque_node_constructor_fn constructor,
                      deque_node_destructor_fn destructor);
/**
 * @brief deque_delete Deleta a estrutura de dados e  libera toda memória
 * alocada desta estrutura. Deve ser invocada quando a estrutura não tem mais
 * utilidade.
 * @param d Ponteiro para a estrutura deque.
 */
void deque_delete(deque_t** d);

/**
 * @brief deque_push_front Insere um elemento no início do deque.
 * @param d Deque.
 * @param Data dado a ser inserido (genérico).
 */
void deque_push_front(deque_t* d,void* data);

/**
 * @brief deque_push_back Insere um elemento no final do deque
 * @param d Deque.
 * @param data Dado a ser inserido (genérico).
 */
void deque_push_back(deque_t* d,void* data);

/**
 * @brief deque_pop_front Remove um elemento do início do deque.
 * @param d Deque.
 */
void deque_pop_front(deque_t* d);


/**
 * @brief deque_pop_back Remove um elemento do final do deque.
 * @param d Deque.
 */
void deque_pop_back(deque_t* d);

/**
 * @brief deque_front Acessa o elemento do início do deque.
 * @param d Deque.
 * @return O elemento do início do deque.
 */
void* deque_front(deque_t* d);

/**
 * @brief deque_back Acessa o elemento do final do deque.
 * @param d Deque.
 * @return O elemento do final do deque.
 */
void* deque_back(deque_t* d);


/**
 * @brief deque_size Retorna o tamanho do deque.
 * @param d Deque.
 * @return Tamanho do deque.
 */
size_t deque_size(deque_t* d);
/**Retorna se o deque está vazio ou não**/
size_t deque_empty(deque_t* d);


#endif
