#ifndef PRIORITY_QUEUE_H_INCLUDED
#define PRIORITY_QUEUE_H_INCLUDED

#include <stdlib.h>
#include <stdbool.h>

typedef struct priority_queue_t {
    int *pqueue;
    size_t size;
    size_t capacity;
} priority_queue_t;


void priority_queue_initialize(priority_queue_t** pq);
void priority_queue_delete(priority_queue_t** pq);
void priority_queue_push(priority_queue_t* pq,int data);
int priority_queue_front(priority_queue_t* pq);
void priority_queue_pop(priority_queue_t* pq);
size_t priority_queue_size(priority_queue_t* pq);
bool priority_queue_empty(priority_queue_t* pq);


#endif