/**
 * ponteiros1.c
**/

#include <stdlib.h>

int main(void){

	/**Ponteiro para inteiro, contém o valor de 
	 * uma posição de memória que é ocupada por um inteiro
	**/ 

	
	int* ptr;
	int inteiro;
	
	/**ptr aponta para o endereço especial NULL**/
	ptr = NULL;
	
	/**Atribuímos a ptr, o endereco da variável inteiro**/
	ptr = &inteiro;

	return(0);
}


