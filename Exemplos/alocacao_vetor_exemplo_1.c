/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Neste programa é explorada
 * a alocação dinâmica de vetores através
 * de ponteiros em C.
**/


#include <stdio.h>
#include <time.h>
#include "alloc.h"
int main(void){
	int n;
	int j;
	srand(time(NULL));
	printf("Digite o tamanho do vetor a ser alocado: ");
	scanf("%d",&n);
    /* Aloca espaço para o vetor e inicializa com zero */
    int* v = callocx(n,sizeof(int));

    /* O vetor é preenchido com números aleatórios.
     * Repare que o acesso á qualquer posição é feito através
     * do operador [], como se fosse um vetor normal.
     * De fato o que é feito é uma aritmética de ponteiros.
     * v[i] = *(v+i) */
	for(j=0;j<n;j++){
		v[j] = rand() % 1000; /**Gera um numero aleatório entre 0 e 999**/
	}

    /* Impressão do vetor */
	for(j=0;j<n;j++){
		printf("v[%d] = %d\n",j,v[j]);
	}

    /* O vetor é desalocado */
    free(v);
	return 0;
}
