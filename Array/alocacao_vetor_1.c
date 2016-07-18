
#include <stdio.h>
#include <time.h>
#include "../Utils/alloc.h"
int main(void){
	int n;
	int j;
	srand(time(NULL));
	printf("Digite o tamanho do vetor a ser alocado: ");
	scanf("%d",&n);
	int* v = callocx(n,sizeof(int)); //alloca e inicializa com zero
	for(j=0;j<n;j++){
		v[j] = rand() % 1000; /**Gera um numero aleatório entre 0 e 999**/
	}
	for(j=0;j<n;j++){
		printf("v[%d] = %d\n",j,v[j]);
	}
	return 0;
}
