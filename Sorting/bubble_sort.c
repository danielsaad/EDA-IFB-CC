#include "bubble_sort.h"


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
