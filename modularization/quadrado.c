#include <stdio.h>
#include "quadrado.h"


static int quadrado_valido(quadrado_t q);

static int quadrado_valido(quadrado_t q){
	if(q.l<=0){
		printf("Não é um quadrado! Lados negativos ou nulos.\n");
		return 0;
	}
	return 1;
}

quadrado_t cria_quadrado(void){
	printf("Digite o lado do quadrado: ");
	quadrado_t q;
	do{
		scanf("%lf",&q.l);
	}while(!quadrado_valido(q));
	return q;
}

double area_quadrado(quadrado_t q){
	return q.l*q.l;
}