/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Neste programa realiza-se a
 * invocação de função através de um ponteiro
 * para a mesma.
 * Utiliza-se um typedef para declarar
 * um tipo de ponteiro para função que retorna
 * um inteiro e recebe dois argumentos inteiros.
**/
#include <stdio.h>

typedef int (*ptr_soma)(int,int);

int soma(int a,int b){
    return(a+b);
}

int main(void){
    /* Declaração de ponteiro para função do tipo
     * ptr_soma */
    ptr_soma ptr = soma;
    printf("Soma = %d.\n",ptr(1,2));
    return 0;
}
