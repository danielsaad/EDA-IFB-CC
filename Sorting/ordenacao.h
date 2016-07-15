#ifndef ORDENACAO_H
#define ORDENACAO_H

void bubblesort(int* vet,int tam);
void countingSort(int* vet,int tam);
void heapsort(int* vet,int size);
void insertionsort(int* vet, int tam);
void mergesort(int* vet, int tam);
void quicksort(int *vet, int esq, int dir);
void radixsort(int* vet, int tam);

int ordenado(int* vet, int tam);

#endif // ORDENACAO_H
