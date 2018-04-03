#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

void bubble_sort(int* v, size_t size){
   int swapped = 1;
   int i;
   for (i = 1; i < size && swapped; i++){
       swapped = 0;
       int j;
       for(j = 0; j < size - i; j++){
           if(v[j] > v[j+1]){
               int temp = v[j];
               v[j] = v[j+1];
               v[j+1] = temp;
               swapped = 1;
           }
       }
   }
}


void quadractic_selection_sort(int*v, int n){
    int root = ceil(sqrt(n));
    int n_blocks = ceil((double) n/root);
    int* counters = calloc(n_blocks,sizeof(int));
    int* v2 = calloc(n,sizeof(int));
    int i,j,k;
    for(i=0;i<n_blocks-1;i++){
        counters[i] = root;
    }
    counters[i] = n % root;

    for(i=0;i<n_blocks;i++){
        bubble_sort(v+root*i,counters[i]);
    }

    j = n-1;
    for(k=0;k<n;k++){
        int max = INT_MIN;
        int index;
        for(i=0;i<n_blocks;i++){
            if(counters[i]==0){
                continue;
            }
            if(max < (v+root*i)[counters[i]-1]){
                max = (v+root*i)[counters[i]-1];
                index = i;
            }
        }
        v2[j--] = max;        
        counters[index]--;
    }
    for(i=0;i<n;i++){
        v[i] = v2[i];
    }
    free(v2);
    free(counters);

}

int main(void){
    int v[] = {2,3,4,6,7,2,4,7,6,1,9,20,1,0,23,-2,4,-6,8};
    int n = 19;
    int i;
    quadractic_selection_sort(v,n);
    for(i = 0;i<n;i++){
        printf("%d ",v[i]);
    }
    return 0;
}