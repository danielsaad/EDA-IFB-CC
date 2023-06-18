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

void deque_initialize(deque_t **d);
void deque_delete(deque_t **d);
void deque_push_back(deque_t *d, int data);
void deque_pop_back(deque_t *d);
void deque_push_front(deque_t *d, int data);
void deque_pop_front(deque_t *d);
int deque_front(deque_t *d);
int deque_back(deque_t *d);
size_t deque_size(deque_t *d);
bool deque_empty(deque_t *d);

#endif