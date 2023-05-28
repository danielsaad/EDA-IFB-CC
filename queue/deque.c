#include "deque.h"
#include "../utils/alloc.h"
#include <assert.h>

void deque_initialize(deque_t **q) {
    (*q) = mallocx(sizeof(deque_t));
    (*q)->front = 0;
    (*q)->back = 3;
    (*q)->size = 0;
    (*q)->capacity = 4;
    (*q)->deque = mallocx(sizeof(int) * 4);
}

void deque_delete(deque_t **q) {
    free((*q)->deque);
    free(*q);
    *q = NULL;
}

void deque_push_back(deque_t *q, int data) {
    if (q->size == q->capacity) {
        size_t old_capacity = q->capacity;
        q->capacity *= 2;
        q->deque = reallocx(q->deque, sizeof(int) * q->capacity);
        if (q->front > q->back) {
            for (size_t i = q->front; i < old_capacity; i++) {
                q->deque[i + old_capacity] = q->deque[i];
            }
            q->front = q->front + old_capacity;
        }
    }
    q->back++;
    if (q->back == q->capacity)
        q->back = 0;
    q->deque[q->back] = data;
    q->size++;
}

void deque_push_front(deque_t *q, int data) {
    if (q->size == q->capacity) {
        size_t old_capacity = q->capacity;
        q->capacity *= 2;
        q->deque = reallocx(q->deque, sizeof(int) * q->capacity);
        if (q->front > q->back) {
            for (size_t i = q->front; i < old_capacity; i++) {
                q->deque[i + old_capacity] = q->deque[i];
            }
            q->front = q->front + old_capacity;
        }
    }
    q->front = q->front == 0? q->capacity-1 : q->front -1;
    q->deque[q->front] = data;
    q->size++;
}

void deque_pop_front(deque_t *q) {
    assert(q->size > 0);
    if (q->size == q->capacity / 4 && q->capacity > 4) {
        size_t new_capacity = q->capacity / 2;
        if (q->front <= q->back) {
            for (size_t i = q->front, j = 0; i <= q->back; i++, j++) {
                q->deque[j] = q->deque[i];
            }
        } else {
            size_t front_len = q->capacity - q->front;
            for (int i = q->back; i >= 0; i--) {
                q->deque[i + front_len] = q->deque[i];
            }
            for (size_t i = q->front, j = 0; i < q->capacity; i++, j++) {
                q->deque[j] = q->deque[i];
            }
        }
        q->front = 0;
        q->back = q->size - 1;
        q->capacity = new_capacity;
        q->deque = reallocx(q->deque, q->capacity * sizeof(int));
    }
    q->front++;
    q->size--;
    if (q->front == q->capacity)
        q->front = 0;
}

void deque_pop_back(deque_t *q) {
    assert(q->size > 0);
    if (q->size == q->capacity / 4 && q->capacity > 4) {
        size_t new_capacity = q->capacity / 2;
        if (q->front <= q->back) {
            for (size_t i = q->front, j = 0; i <= q->back; i++, j++) {
                q->deque[j] = q->deque[i];
            }
        } else {
            size_t front_len = q->capacity - q->front;
            for (int i = q->back; i >= 0; i--) {
                q->deque[i + front_len] = q->deque[i];
            }
            for (size_t i = q->front, j = 0; i < q->capacity; i++, j++) {
                q->deque[j] = q->deque[i];
            }
        }
        q->front = 0;
        q->back = q->size - 1;
        q->capacity = new_capacity;
        q->deque = reallocx(q->deque, q->capacity * sizeof(int));
    }
    q->back = q->back == 0? q->capacity-1 : q->back -1;
    q->size--;
}

int deque_front(deque_t *q) {
    assert(q->front < q->capacity);
    return q->deque[q->front];
}

int deque_back(deque_t *q) {
    assert(q->front < q->capacity);
    return q->deque[q->back];
}

size_t deque_size(deque_t *q) {
    return q->size;
}

bool deque_empty(deque_t *q) {
    return deque_size(q) == 0;
}