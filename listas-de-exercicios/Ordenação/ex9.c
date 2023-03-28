#include <stdio.h>

void swap(int *v, int i, int j){
    int t = v[i];
    v[i] = v[j];
    v[j] = t;
}

size_t partition(int *vet, int esq,int dir,int pivot){
    size_t pos, i;
    swap(vet, pivot, dir);
    pos = esq;
    for(i = esq; i < dir; i++){
        if (vet[i] < vet[dir]){
            swap(vet, i, pos);
            pos++;
        }
    }
    swap(vet, dir, pos);
    return pos;
}

int quick_find(int* v,int l,int r,int k){
	int p = partition(v,l,r,r);
	if(k==p-l){
		return v[p];
	}
	else if (k<p-l){
		return quick_find(v,l,p-1,k);
	}
	else{
		return quick_find(v,p+1,r,(k-(p-l)-1));
	}
}

int main(void){
	int v[] = {1,5,3,0,2,4,9,10,12,18,11,9,7};
	int k;
	for(k=0;k<13;k++){
		printf("O %d menor elemento é %d.\n",k,quick_find(v,0,12,k));
	}
	return 0;
}