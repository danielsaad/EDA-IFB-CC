#include <stdio.h>

int main(void) {

    /* Ponteiro para inteiro, contém o valor de
     * uma posição de memória que é ocupada por um inteiro*/
    int *ptr;
    int inteiro = 0;

    /* ptr aponta para o endereço especial NULL**/
    ptr = NULL;

    /* Atribuímos a ptr, o endereco da variável inteiro */
    ptr = &inteiro;
    printf("O valor do ponteiro ptr = %p.\n", ptr);
    return 0;
}