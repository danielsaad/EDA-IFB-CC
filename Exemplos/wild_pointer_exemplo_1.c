/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Este programa mostra um exemplo
 * de um ponteiro selvagem. A variável num só
 * existe no escopo de func, e portanto, seu endereço
 * não é mais válido quando a função termina.
**/

#include <stdio.h>

int* func(void){
    int num = 1234;
    /* ... */
    return &num;
}

int main(void){
    /* A wild pointer has appeared! */
    int* ptr = func();
    printf("O valor do inteiro num = %d.\n",*ptr);
    return 0;
}
