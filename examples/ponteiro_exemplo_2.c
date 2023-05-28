/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Este programa aborda conceitos
 * básicos sobre ponteiros e deferência.
 **/
#include <stdio.h>

int main() {
    /* Ponteiro para inteiro, contém o valor de uma posição
    de memória que é ocupada por um inteiro */
    int *ptr;
    /*um inteiro*/
    int var = 0;
    printf("Var = %d\n", var);
    /*O valor de ptr aponta agora para o endereço de
     memória que corresponde à variável var. */
    ptr = &var;
    /*Modificamos o *conteúdo* da regiao
    de memoria apontada por ptr*/
    (*ptr) = 1; // Equivale a fazer var=1
    /*Note que agora o novo valor de var é 1*/
    printf("Var = %d\n", var);
    printf("Var = %d\n", *ptr);
    return (0);
}