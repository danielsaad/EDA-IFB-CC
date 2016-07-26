/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Neste programa conceitos básicos
 * sobre ponteiros são explicados.
**/

#include <stdlib.h>
#include <stdio.h>
int main(void){

    /* Ponteiro para inteiro, contém o valor de
     * uma posição de memória que é ocupada por um inteiro*/
    int* ptr;
    int inteiro;
	
    /* ptr aponta para o endereço especial NULL**/
    ptr = NULL;
	
    /* Atribuímos a ptr, o endereco da variável inteiro */
    ptr = &inteiro;
    printf("O valor do ponteiro ptr = %p.\n",ptr);
    return(0);
}


