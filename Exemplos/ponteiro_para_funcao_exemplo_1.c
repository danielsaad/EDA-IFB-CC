/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Neste programa realiza-se a
 * invocação de função através de um ponteiro
 * para a mesma.
**/
#include <stdio.h>

int soma(int a,int b){
    return(a+b);
}

int main(void){
    /* Declaração de ponteiro para função que
     * retorna um inteiro e recebe dois */
    int (*ptr)(int,int);
    ptr = soma;
    printf("Soma = %d.\n",ptr(1,2));
    return 0;
}
