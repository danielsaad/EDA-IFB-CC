#include <string.h>
#include <stdio.h>
#include <time.h>
#include "alloc.h"
#include "priority_queue.h"


void* int_constructor(void* data){
    void* ptr = mallocx(sizeof(int));
    memcpy(ptr,data,sizeof(int));
    return ptr;
}

void int_destructor(void* data){
    free (data);
}


int int_comparator(const void* a,const void *b){
    if(*(int*)a < *(int*)b){
        return -1;
    }
    else if( *(int*)a == *(int*)b){
        return 0;
    }
    return 1;
}


int main(void){
    srand(time(NULL));
    priority_queue_t* pq;
    priority_queue_initialize(&pq,int_constructor,int_destructor,int_comparator);
    int i;
    for(i=0;i<1000;i++){
        int value = rand()%10000;
        printf("Inserindo %d na fila de prioridades.\n",value);
        priority_queue_push(pq,&value);
    }
    while(!priority_queue_empty(pq)){
        int value = * (int*)priority_queue_front(pq);
        printf("Valor retirado da fila de prioridades: %d\n",value);
        priority_queue_pop(pq);
    }
    priority_queue_delete(&pq);
    return 0;
}
