/*
 * alocacao1.c
 */

#include <stdio.h>
#include <stdlib.h>

int main(void){

	//Ponteiros inicialmente apontam para uma posição de memória arbitrária.
	//É necessário atribuir a eles uma posição de memória válida que pertença ao seu programa.

	int* ptr;

	//Podemos requisitar ao sistema operacional que ele aloque
	//uma porção de memória para o programa e devolva o início dessa posição de memória.

	//O operador new é responsável por fazer essa requisição ao sistema operacional

	ptr = malloc(sizeof(int));

	//Dessa forma, ponteiros podem apontar para posições de
	//memória alocadas pelo sistema operaconal

	*ptr = 3; //modificamos o conteúdo da memória alocada e apontada por ptr

    printf("Valor do conteúdo de ptr = %p\n",ptr);
    printf("Valor do conteúdo apontado por ptr = %d\n",*ptr);
    free (ptr); //libera a memória alocada com delete

	return 0;

}




