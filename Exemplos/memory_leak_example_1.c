/**
 * memory-leak1.c
 **/

#include <stdlib.h>
int main(void){

	int* ptr = malloc(sizeof(int)*100000); /**aloca um vetor de 100000 posições.**/

	/** MEMORY LEAK: atribui um novo endereço de memória para ptr
	 * 	sem desalocar o bloco de memória alocado **/
	ptr = NULL; 
	return(0);
}


