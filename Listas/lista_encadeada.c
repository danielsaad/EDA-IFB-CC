#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "lista_encadeada.h"
#include "../Utils/alloc.h"


no_lista_encadeada_t* cria_no_lista_encadeada(int dado){
    no_lista_encadeada_t* no = mallocx(sizeof(no_lista_encadeada_t));
    no->dado = dado;
    return no;
}

void inicializa_lista_encadeada(lista_encadeada_t** l){
    (*l) = mallocx(sizeof(lista_encadeada_t));
    (*l)->cabeca = NULL;
    (*l)->cauda = NULL;
    (*l)->tamanho = 0;
}

void deleta_lista_encadada(lista_encadeada_t** l){
    no_lista_encadeada_t* aux = (*l)->cabeca;
    no_lista_encadeada_t* aux2 = aux->prox;
    while(aux!=NULL){
        free(aux);
        aux = aux2;
        aux2 = aux->prox;
    }
    free(*l);
    *l = NULL;
}

void insere_lista_encadeada(lista_encadeada_t* l,size_t i,int dado){
    if(i<0 || i> l->tamanho){
        perror("Inserção em lista encadeada em posição inválida!");
        exit(EXIT_FAILURE);
    }
    no_lista_encadeada_t* no = cria_no_lista_encadeada(dado);
    if(l->tamanho==0){ /**Inserção em lista vazia**/
        l->cabeca = no;
        l->cauda = no;
        no->prox = NULL;
    }
    else if(i==0){ /**Inserção na cabeça em lista não vazia**/
        no->prox = l->cabeca;
        l->cabeca = no;
    }
    else if(i== l->tamanho){ /**Inserção na cauda em lista não vazia**/
        l->cauda->prox = no;
        no->prox = NULL;
        l->cauda = no;
    }
    else{ /**Inserção no meio**/
        no_lista_encadeada_t* aux = l->cabeca;
        int j;
        for(j=0;j<i-1;j++){
            aux = aux->prox;
        }
        no->prox = aux->prox;
        aux->prox = no;
    }
    l->tamanho++;
}

void remove_lista_encadeada(lista_encadeada_t* l,size_t i){
    if(i<0 ||  i>=l->tamanho){
        perror("Remoção em posição inválida da lista!");
        exit(EXIT_FAILURE);
    }
    no_lista_encadeada_t* aux;
    if(l->tamanho==1){ /**a lista só possui um elemento**/
        aux = l->cabeca;
        l->cabeca=NULL;
        l->cauda=NULL;
    }
    else if(i==0){ /**Remoção da cabeça**/
        aux = l->cabeca;
        l->cabeca = l->cabeca->prox;

    }
    else if(i==l->tamanho-1){ /**Remoção da cauda**/
        aux = l->cabeca;
        while(aux->prox!=l->cauda){ /**Percorre a lista até chegar no elemento que precede a cauda**/
            aux = aux->prox;
        }
        l->cauda = aux;
        aux = aux->prox;
        l->cauda->prox = NULL;
    }
    else{ /**Remoção no meio**/
        int j;
        no_lista_encadeada_t* aux2;
        aux2 = l->cabeca;
        for(j=0;j<i-1;j++){
            aux2 = aux2->prox;
        }
        aux = aux2->prox;
        aux2->prox = aux->prox;
    }
    free(aux);
    l->tamanho--;
}

