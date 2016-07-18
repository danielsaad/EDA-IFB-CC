/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Neste programa realiza-se a
    alocação dinâmica de memória de uma matriz.
    Nele são lidas os número de linhas e colunas
    e a matriz é preenchia aleatóriamente através
    da função rand();
**/


#include <stdio.h>
#include <time.h>
#include "alloc.h"


int main(void){
	int l,c;
	int i,j;
	srand(time(NULL));
	printf("Digite o número de linhas da matriz: ");
	scanf("%d",&l);
	printf("Digite o número de colunas da matriz: ");
	scanf("%d",&c);
    /* Alocamos um vetor de ponteiros */
    int** m = callocx(l,sizeof(int*));
    /* O ponteiro zero recebe o espaço da matriz
     * isto é, l*c */
	m[0] = callocx(l*c,sizeof(int));
    /* Cada um dos ponteiros recebe o início de uma região
     * de memória apontada por m[0] */
	for(j=1;j<l;j++){
		m[j] = m[0]+j*c;
	}
	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
            m[i][j] = rand() % 1000; /* Um inteiro aleatório [0,999] é gerado */
		}
	}
    /* Impressão da matriz */
	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			printf("%3d ",m[i][j]);
		}
		printf("\n");
	}
    /* O espaço alocado é liberado */
    free(m[0]);
    free(m);

	return 0;
}
