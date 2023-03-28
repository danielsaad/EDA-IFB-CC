#include <stdio.h>
#include <stdlib.h>

int* intersecao(int* v1,int* v2,int n,int m,int* tam){
	int i,j;
	int l=0;
	int k = n > m ? m : n;
	int* v3 = malloc(sizeof(int)*k);
	if(v3==NULL){
		printf("Erro na alocação.\n");
		exit(EXIT_FAILURE);
	}
	int igual;
	for(i=0;i<n;i++){
		igual = 0;
		for(j=0;j<m;j++){
			if(v1[i]==v2[j]){
				igual = 1;
			}
		}
		if(igual){
			int m;
			int repetido = 0;
			for(m=0;m<l;m++){
				if(v3[m]==v1[i]){
					repetido = 1;
				}
			}
			if(!repetido){
				v3[l++] = v1[i];
			}
		}
	}
	*tam = l;
	return v3;
}

int main(){
	int n,m,l;
	printf("Digite os valores de n e m: ");
	scanf("%d %d",&n,&m);
	int *v1,*v2;
	v1 = malloc(n*sizeof(int));
	v2 = malloc(m*sizeof(int));
	if(v1==NULL || v2==NULL){
		printf("Erro na alocação.\n");
		exit(EXIT_FAILURE);
	}
	int i;
	for(i=0;i<n;i++){
		printf("v1[%d] ? ",i);
		scanf("%d",&v1[i]);
	}
	for(i=0;i<m;i++){
		printf("v2[%d] ? ",i);
		scanf("%d",&v2[i]);
	}
	l = 0;
	int* v3 = intersecao(v1,v2,n,m,&l);
	for(i=0;i<l;i++){
		printf("v3[%d] = %d\n",i,v3[i]);
	}
	free(v1);
	free(v2);
	free(v3);
	return 0;
}