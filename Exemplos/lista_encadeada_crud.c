#include <stdio.h>
#include "../Listas/lista_encadeada.h"


void imprime_lista(lista_encadeada_t* l){
    no_lista_encadeada_t* aux;
    printf("\n\n");
    for(aux = l->cabeca;aux!=NULL;aux=aux->prox){
        printf("%d -> ",aux->dado);
    }
    printf("NULL\n\n");
}

void insere_elemento(lista_encadeada_t* l){
    int valor,pos;
    printf("Digite o valor que deseja inserir: ");
    scanf("%d",&valor);
    printf("Digite a posição da lista que deseja inserir este valor: ");
    scanf("%d",&pos);
    insere_lista_encadeada(l,pos,valor);
    imprime_lista(l);
}

void remove_elemento(lista_encadeada_t* l){
    int pos;
    printf("Digite a posição da lista que deseja remover:");
    scanf("%d",&pos);
    remove_lista_encadeada(l,pos);
    imprime_lista(l);
}

int main(void){
    lista_encadeada_t* l;
    inicializa_lista_encadeada(&l);
    int opcao;
    do{
        printf("1 - Inserir um elemento na lista.\n");
        printf("2 - Remover um elemento da lista.\n");
        printf("3 - Imprimir a Lista.\n");
        printf("9 - Sair.\n");
        scanf("%d",&opcao);
        if(opcao==1)
            insere_elemento(l);
        else if(opcao==2)
            remove_elemento(l);
        else
            imprime_lista(l);
    }while(opcao!=9);
    deleta_lista_encadada(&l);
    return 0;
}
