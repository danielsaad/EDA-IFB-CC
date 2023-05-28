/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Neste programa é explorada
 * a alocação dinâmica de structs através
 * de ponteiros em C.
 **/

#include <stdio.h>
#include <stdlib.h>

typedef struct ExemploStruct {
    int a, b, c;
} ExemploStruct;

int main(void) {
    ExemploStruct *ptr_estrutura;
    /* Aloca dinamicamente uma estrutura e passa o endereco inicial
     * da estrutura para o ponteiro */
    ptr_estrutura = malloc(sizeof(ExemploStruct));
    if (ptr_estrutura == NULL) {
        printf("Erro de alocação.\n");
        exit(EXIT_FAILURE);
    }
    /* O acesso em membros de estruturas apontadas por
     * ponteiros é feito através do operador seta.
     * Em resumo: (*estrutura_ptr).a é equivalente a
     * estrutura_ptr->a. Preferimos a segunda forma por ser
     * mais legível */
    ptr_estrutura->a = 3;
    ptr_estrutura->b = 4;
    ptr_estrutura->c = 5;
    /* Liberação do espaço alocado */
    free(ptr_estrutura);
    return (0);
}