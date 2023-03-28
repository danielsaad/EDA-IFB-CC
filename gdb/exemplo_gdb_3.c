#include <stdio.h>

int acha_menor(int* v,int n){
	int menor;
	int i;
	for(i=0;i<n;i++){
		if(v[i]<menor){
			menor = v[i];
		}
	}
	return menor;
}

int main(){
	int v[5];
	int i;
	for(i=0;i<5;i++){
		printf("V[%d]: ",i);
		scanf("%d",&v[i]);
	}
	int menor = acha_menor(v,5);
	printf("Menor = %d\n.",menor);
}