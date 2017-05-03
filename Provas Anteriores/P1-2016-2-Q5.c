#include <stdio.h>
#include <stdlib.h>


void heapify(int* v,int i, int n){
	int l,r,maior;
	maior = i;
	while(i<n){
		l = 2*i+1;
		r = 2*i+2;
		if(l<n && v[i]<v[l]){
			maior = l;
		}
		if(r<n && v[maior]<v[r]){
			maior = r;
		}
		if(maior == i)
			break;
		int aux = v[i];
		v[i] = v[maior];
		v[maior] = aux;

		i = maior;
	}
}


void make_heap(int* v,size_t n){
	int i;
	for(i=n/2;i>=0;i--){
		heapify(v,i,n);
	}
}



void imprime_k_maiores(int* v,size_t n,int k){
	int i;
	make_heap(v,n);
	for(i=0;i<k;i++){
		printf("%d\n",v[0]);
		int aux = v[n-i-1];
		v[n-i-1] = v[0];
		v[0] = aux;
		heapify(v,0,n-i-1);
	}	
}


int main(void){
	int v[] = {4,1,3,2,16,9,10,14,8,7};	
	imprime_k_maiores(v,10,4);
	return 0;
}