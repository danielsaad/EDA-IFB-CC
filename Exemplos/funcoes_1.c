
#include <stdio.h>
#include <stdlib.h>
/**
 * Funções são declaradas da seguinte forma:
 * <tipo de retorno> <nome da função> ( <argumento 1>, <argumento 2>, ... ){
 * 		CORPO DA FUNÇÃO
 * }
 */

/** Funcao que retorna o dobro de um inteiro **/
int exemploFuncao(int a){
	return(2*a);
}

/** Funcao que retorna um ponteiro para inteiro contendo
 *  a metade de um inteiro**/
int* exemploFuncao2(int a){
	int* b = malloc(sizeof(int));
    *b = a/2;
	return(b);
}


int main(void){
	int x = 10;
	int* p;
	
	p = exemploFuncao2(x);
	
	printf("Dobro de %d = %d\n",x,exemploFuncao(x));
	printf("Metade truncada de %d = %d\n",x,*p);

    return(0);
}


/** Funcao que retorna a raiz de um inteiro **/
