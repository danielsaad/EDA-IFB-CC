/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Neste programa é ilustrado o fato
 * de que vetores podem ser vistos como ponteiros,
 * e vice-versa através da aritmética de ponteiros
**/

#include <stdio.h>

int main(void){

	char* ptr;
	char v[] = {'a','b','a','c','a','t','e','\0'};
	
	/**O nome de um vetor equivale ao endereço inicial de memória
	 * ocupado por ele. Logo p1 agora aponta para este mesmo
	 * endereco.**/		
	ptr = v; 
    printf("String original: %s\n",v);
	
	ptr[2] = 'd';	
	
	printf("String modificada: %s\n",v);

	return(0);
}


