#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

#include <stdbool.h>
#include <stdlib.h>

typedef struct deque_t {
    size_t front;
    size_t back;
    size_t size;
    size_t capacity;
    int *deque;
} deque_t;

void deque_initialize(deque_t **q);
void deque_delete(deque_t **q);
void deque_push_back(deque_t *q, int data);
void deque_pop_back(deque_t *q);
void deque_push_front(deque_t *q, int data);
void deque_pop_front(deque_t *q);
int deque_front(deque_t *q);
int deque_back(deque_t *q);
size_t deque_size(deque_t *q);
bool deque_empty(deque_t *q);

#endif