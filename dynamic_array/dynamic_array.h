#include <stdlib.h>

typedef struct {
    int *v;          // vetor dinâmico
    size_t capacity; // capacidade do vetor dinãmico
    size_t size;     // tamanho do vetor dinâmico
} dynamic_array_t;

/**
 * @brief Inicializa um vetor dinâmico
 *
 * @param arr ponteiro de vetor dinâmico a ser modificado por referência
 */
void dynamic_array_initialize(dynamic_array_t **arr);

/**
 * @brief Duplica a capacidade de um vetor dinâmico
 *
 * @param arr vetor dinâmico
 */
void dynamic_array_double_capacity(dynamic_array_t *arr);

/**
 * @brief Reduz a capacidade do vetor dinâmico pela metade
 *
 * @param arr vetor dinâmico
 */
void dynamic_array_halve_capacity(dynamic_array_t *arr);

/**
 * @brief Obtém a capacidade atual do vetor dinâmico
 * 
 * @param arr vetor dinâmico
 * @return size_t capacidade atual do vetor dinâmico
 */
size_t dynamic_array_capacity(dynamic_array_t *arr);

/**
 * @brief Insere o elemento x ao final do vetor dinâmico arr
 *
 * @param arr ponteiro de vetor dinâmico a ser modificado por referência
 * @param x elemento a ser inserido ao final do vetor dinâmico
 */
void dynamic_array_push_back(dynamic_array_t *arr, int x);

/**
 * @brief Remove o elemento x ao final do vetor dinãmico arr. Para isto,
 * só é necessário decrementar o tamanho de arr
 *
 * @param arr ponteiro de vetor dinâmico a ser modificado por referência
 */
void dynamic_array_pop_back(dynamic_array_t *arr);

/**
 * @brief Deleta o vetor dinãmico completamente da memória.
 *
 * @param arr ponteiro de vetor dinâmico a ser modificado por referência.
 */

void dynamic_array_delete(dynamic_array_t **arr);

/**
 * @brief Retorna o último elemento do array dinâmico.
 *
 * @param arr array dinãmico.
 * @return int último elemento do array dinâmico.
 */
int dynamic_array_back(dynamic_array_t *arr);

/**
 * @brief Retorna o primeiro elemento do array dinâmico.
 *
 * @param arr array dinãmico.
 * @return int primeiro elemento do array dinâmico.
 */
int dynamic_array_front(dynamic_array_t *arr);

/**
 * @brief Retorna o tamanho atual do vetor dinâmico.
 *
 * @param arr vetor dinâmicio
 * @return size_t tamanho do vetor dinâmico
 */
size_t dynamic_array_size(dynamic_array_t *arr);