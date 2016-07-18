
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
	int** m = callocx(l,sizeof(int*)); //alloca e inicializa com zero
	m[0] = callocx(l*c,sizeof(int));
	for(j=1;j<l;j++){
		m[j] = m[0]+j*c;
	}
	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			m[i][j] = rand() % 1000; /**Gera um numero aleatório entre 0 e 999**/
		}
	}
	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			printf("%3d ",m[i][j]);
		}
		printf("\n");
	}

	return 0;
}
