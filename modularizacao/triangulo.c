#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "triangulo.h"

/* Esta função faz sentido dentro deste módulo apenas,
	por isto ela não é declarada no arquivo triangulo.h,
	e portanto, não é exportada
*/
static int triangulo_valido(triangulo_t t);

triangulo_t cria_triangulo(void){
	triangulo_t t;
	do{
		printf("Digite o primeiro lado do triângulo: ");
		scanf("%lf",&t.a);
		printf("Digite o segundo lado do triângulo: ");
		scanf("%lf",&t.b);
		printf("Digite o terceiro lado do triângulo: ");
		scanf("%lf",&t.c);
	}while(!triangulo_valido(t));
	return t;
}


/* Verifica se os dados informados formam
	um triângulo
*/
static int triangulo_valido(triangulo_t t){
	if(t.a<=0 || t.b<=0 || t.c<=0){
		printf("Não é um triângulo! Lados negativos ou nulos.\n");
		return 0;
	}
	if(abs(t.b-t.c)<t.a && t.a < t.b+t.c &&
		abs(t.a-t.c)<t.b && t.b<t.a+t.c  &&
		abs(t.a-t.b)<t.c && t.c<t.a+t.b){
		return 1;
	}
	else{
		printf("Não é um triângulo! Condição de existência não respeitada.\n");
	}
	return 0;
}

/* Função que calcula a área de um triângulo de acordo
	com o teorema de Herão: https://pt.wikipedia.org/wiki/Teorema_de_Her%C3%A3o
*/ 
double area_triangulo(triangulo_t t){
	double p = (t.a+t.b+t.c)/2;
	return(sqrt(p*(p-t.a)*(p-t.b)*(p-t.c)));
}
