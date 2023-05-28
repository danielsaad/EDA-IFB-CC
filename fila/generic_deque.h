#ifndef GENERIC_DEQUE_H_INCLUDED
#define GENERIC_DEQUE_H_INCLUDED

#include <stdlib.h>

/**
 * @brief Definição do tipo construtor: um ponteiro para função que retorna
 * o objeto alocado e recbe o objeto a ser copiado.
 */
typedef void* (*generic_deque_node_constructor_fn) (void*);


/**
 * @brief Definição do tipo destrutor: um ponteiro para função que não retorna
 * nada e recebe o dado a ser destruído.
 */
typedef void (*generic_deque_node_destructor_fn)(void *);


/**
 * @brief generic_deque_node_t Definição do nó do generic_deque.
 * Possui um ponteiro para o dado genérico alocado pelo construtor,
 * um ponteiro para o próximo elemento e um elemento para o próximo.
 * O generic_deque é implementado através da estrutura list duplamento encadeada.
 */


typedef struct generic_deque_node_t{
    struct generic_deque_node_t* next;
    struct generic_deque_node_t* prev;
    void* data;
}generic_deque_node_t;

/**
 * @brief generic_deque_iterator_t Apelido para nó do generic_deque. Utilizado quando queremos
 * iterar no generic_deque.
 */
typedef generic_deque_node_t* generic_deque_iterator_t;


/**
 * @brief generic_deque_t Tipo generic_deque. Possui ponteiros para frente, final e ponteiros
 * para as funções construtora, destrutora. O tamanho do generic_deque também está
 * presente.
 */
typedef struct generic_deque_t{
    struct generic_deque_node_t* front;
    struct generic_deque_node_t* back;
    generic_deque_node_constructor_fn constructor;
    generic_deque_node_destructor_fn destructor;
    size_t size;
}generic_deque_t;


/**
 * @brief generic_deque_initialize Inicializa a estrutura generic_deque.
 * @param d Ponteiro para estrutura generic_deque.
 * @param constructor Função construtora.
 * @param destructor Função destrutora.
 */
void generic_deque_initialize(generic_deque_t** d,generic_deque_node_constructor_fn constructor,
                      generic_deque_node_destructor_fn destructor);
/**
 * @brief generic_deque_delete Deleta a estrutura de dados e  libera toda memória
 * alocada desta estrutura. Deve ser invocada quando a estrutura não tem mais
 * utilidade.
 * @param d Ponteiro para a estrutura generic_deque.
 */
void generic_deque_delete(generic_deque_t** d);

/**
 * @brief generic_deque_push_front Insere um elemento no início do generic_deque.
 * @param d Deque.
 * @param Data dado a ser inserido (genérico).
 */
void generic_deque_push_front(generic_deque_t* d,void* data);

/**
 * @brief generic_deque_push_back Insere um elemento no final do generic_deque
 * @param d Deque.
 * @param data Dado a ser inserido (genérico).
 */
void generic_deque_push_back(generic_deque_t* d,void* data);

/**
 * @brief generic_deque_pop_front Remove um elemento do início do generic_deque.
 * @param d Deque.
 */
void generic_deque_pop_front(generic_deque_t* d);


/**
 * @brief generic_deque_pop_back Remove um elemento do final do generic_deque.
 * @param d Deque.
 */
void generic_deque_pop_back(generic_deque_t* d);

/**
 * @brief generic_deque_front Acessa o elemento do início do generic_deque.
 * @param d Deque.
 * @return O elemento do início do generic_deque.
 */
void* generic_deque_front(generic_deque_t* d);

/**
 * @brief generic_deque_back Acessa o elemento do final do generic_deque.
 * @param d Deque.
 * @return O elemento do final do generic_deque.
 */
void* generic_deque_back(generic_deque_t* d);


/**
 * @brief generic_deque_size Indica o tamanho do generic_deque.
 * @param d Deque.
 * @return Tamanho do generic_deque.
 */
size_t generic_deque_size(generic_deque_t* d);

/**
 * @brief generic_deque_empty Verifica se o generic_deque está vazio.
 * @param d Deque.
 * @return Verdadeiro(1) se o Deque está vazio e Falso(0), caso contrário.
 */
size_t generic_deque_empty(generic_deque_t* d);


#endif
