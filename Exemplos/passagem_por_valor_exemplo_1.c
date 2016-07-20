/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Neste programa é explorada
 * a passagem por valor em funções na
 * linguagem C, que corresponde a única
 * maneira de passagem de variáveis como parâmetros
 * nesta linguagem..
**/
 
#include <stdio.h>

/* Passagem por valor, cria-se uma cópia x da variável
 * passada como argumento */

double cubo(double x){
	return(x*x*x);
}

int main(void){
    double a = 3;
    printf("O cubo de %f é %f\n",a,cubo(a));
	return(0);
}
	
