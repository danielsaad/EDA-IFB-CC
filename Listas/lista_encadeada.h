#ifndef LISTA_ENCADEADA_H_INCLUDED
#define LISTA_ENCADEADA_H_INCLUDED
#include "../Utils/tipos.h"



/**
    A nossa lista encadeada consiste de vários nós,
    que possuem o tipo no_lista_encadeada_t
**/
typedef struct no_lista_encadeada_t{
    int dado; /*dado*/
    struct no_lista_encadeada_t* prox; /*ponteiro para o próximo elemento*/
}no_lista_encadeada_t;


typedef struct lista_encadeada_t{
    no_lista_encadeada_t* cabeca;
    no_lista_encadeada_t* cauda;
    int tamanho; /*tamanho da lista*/
}lista_encadeada_t;

/**Função auxiliar que aloca dinâmicamente um nó da lista**/
no_lista_encadeada_t* cria_no_lista_encadeada(int dado);
/**Inicializa uma lista encadeada**/
void inicializa_lista_encadeada(lista_encadeada_t** l);
/**Deleta uma lista encadeada e retorna o ponteiro como NULL**/
void deleta_lista_encadada(lista_encadeada_t** l);
/**Insere um elemento na posição i de uma lista encadeada com conteúdo dado*/
void insere_lista_encadeada(lista_encadeada_t* l, size_t i, int dado );
/**Remove o elemento da lista que ocupa a posição i**/
void remove_lista_encadeada(lista_encadeada_t* l,size_t i);

#endif // LISTA_ENCADEADA_H_INCLUDED
