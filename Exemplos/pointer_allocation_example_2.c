/**alocacao2.c**/

#include <stdlib.h>

typedef struct ExemploStruct{
	int a,b,c;
}ExemploStruct;

int main(void){
	int* vetor;
	ExemploStruct* estrutura;

	/** Aloca dinamicamente uma estrutura e passa o endereco inicial
	 * da estrutura para o ponteiro**/
	estrutura = malloc(sizeof(ExemploStruct)); /** aloca uma estrutura dinamicamente**/

	/**Aloca dinamicamente um vetor de inteiros 
	 * de 10 posições e passa o endereço inicial
	 * desse vetor para o ponteiro **/	
	vetor = malloc(sizeof(int)*10);
	
	
	estrutura->a=3;
	estrutura->b=4;
	estrutura->c=5;
	
	vetor[2] = 3;
	vetor[9] = 0; /**Ultimo elemento da porção de memoria apontada por vetor**/
				  
    free (estrutura);
    free (vetor);

	return(0);
	
}
