/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Este programa corrige o anterior
 * ao alocar dinâmicamente a variável num.
 * Ao alocarmos dinâmicamente, o endereço persiste
 * até que um free() seja utilizado, logo, o exemplo
 * abaixo não configura um ponteiro selvagem;
**/

#include <stdio.h>
#include <stdlib.h>

int* func(void){
    int* num = malloc(sizeof(int));
    if(num==NULL){
        printf("Erro de alocação.\n");
    }
    *num = 1234;
    return num;
}

int main(void){
    /* A wild pointer has appeared! */
    int* ptr = func();
    printf("O valor do inteiro num = %d.\n",*ptr);
    free(ptr);
    return 0;
}
