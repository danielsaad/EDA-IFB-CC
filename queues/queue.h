#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdbool.h>
#include <stdlib.h>

typedef struct queue_t {
    size_t front;
    size_t back;
    size_t size;
    size_t capacity;
    int *queue;
} queue_t;

void queue_initialize(queue_t **q);
void queue_delete(queue_t **q);
void queue_push(queue_t *q, int data);
void queue_pop(queue_t *q);
int queue_front(queue_t *q);
size_t queue_size(queue_t *q);
bool queue_empty(queue_t *q);

#endif