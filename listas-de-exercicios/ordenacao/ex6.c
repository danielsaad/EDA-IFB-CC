#include <stdio.h>
#include <stdlib.h>

void bucket_sort(int* v,int n){
    int* counters;
    int min,max;
    min = v[0];
    max = v[0];
    int i,j;
    /* Encontra o menor e o maior elementos */
    for(i=1;i<n;i++){
        if(v[i]<min){
            min = v[i];
        }
        else if(v[i]>max){
            max = v[i]; 
        }
    }
    /* Cria o vetor de baldes */
    counters = calloc(max-min+1,sizeof(int));
    for(i=0;i<n;i++){
        counters[v[i]-min]++;
    }
    /* Utiliza o vetor de baldes para ordenar*/
    for(i=0,j=0;i<max-min+1;i++){
        while(counters[i]>0){
            v[j++] = i+min;
            counters[i]--;
        }     
    }
    free(counters);
}

int main(void){
    int v[] = {2,3,4,6,7,2,4,7,6};
    int n = 9;
    int i;
    bucket_sort(v,n);
    for(i = 0;i<n;i++){
        printf("%d ",v[i]);
    }
    return 0;
}