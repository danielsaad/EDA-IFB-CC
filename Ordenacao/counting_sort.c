/*
 * Daniel Saad Nogueira Nunes 06/81792
 * Counting Sort
 */

#include <stdio.h>
#include <string.h>
#include "../Utils/alloc.h"
#include "counting_sort.h"
/*
 * Complexidade do Counting Sort
 * O(n+m)
 * n = ordem do vetor
 * m = valor máximo que um vetor pode ter
 */


void counting_sort(int* v,size_t size){
	int i;
    int largest;
    int *c;
    int *v2;

    v2 = mallocx(sizeof(int)*size);
    memcpy(v2,v,sizeof(int)*size);


    largest = v2[0];
    for(i=0;i<size;i++){
        if(largest<v2[i])
            largest = v2[i];
	}

    c = callocx(largest+1,sizeof(int));
    for(i=0;i<size;i++){
        c[v2[i]]++;
    }

    for(i=1;i<=largest;i++){
        c[i] += c[i-1];
	}
    for(i=size-1;i>=0;i--){
        v[--c[v2[i]]] = v2[i];
    }
    free(c);
    free(v2);
}
