#include "alloc.h"
#include "priority_queue.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(void) {
    srand(time(NULL));
    priority_queue_t *pq;
    priority_queue_initialize(&pq);
    int i;
    for (i = 0; i < 1000; i++) {
        int value = rand() % 10000;
        printf("Inserindo %d na fila de prioridades.\n", value);
        priority_queue_push(pq, value);
    }
    while (!priority_queue_empty(pq)) {
        printf("Valor retirado da fila de prioridades: %d\n",
               priority_queue_front(pq));
        priority_queue_pop(pq);
    }
    priority_queue_delete(&pq);
    return 0;
}