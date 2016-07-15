/**
 * passagem-por-referencia2.c
 **/

#include <stdio.h>

/** Em C, vetores sempre são passados por referência **/
 
void soma(int x[],int n){
	int i;
	for(i=0;i<n;i++)
		x[i]++;
}

int main(void){
	int i;
	int x[] = {1,2,3,4,5,6};
	int n = 6;
	printf("Vetor original: ");
    for(i=0;i<n;i++)
		printf("%d ",x[i]);
	printf("\n");

	soma(x,6);
	
	printf("Vetor modificado: ");
    for(i=0;i<n;i++)
		printf("%d ",x[i]);
	printf("\n");
	return(0);
}
