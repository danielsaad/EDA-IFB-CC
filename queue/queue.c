#include "queue.h"
#include "../utils/alloc.h"
#include <assert.h>

void queue_initialize(queue_t **q) {
    (*q) = mallocx(sizeof(queue_t));
    (*q)->front = 0;
    (*q)->back = 3;
    (*q)->size = 0;
    (*q)->capacity = 4;
    (*q)->queue = mallocx(sizeof(int) * 4);
}

void queue_delete(queue_t **q) {
    free((*q)->queue);
    free(*q);
    *q = NULL;
}

void queue_push(queue_t *q, int data) {
    if (q->size == q->capacity) {
        size_t old_capacity = q->capacity;
        q->capacity *= 2;
        q->queue = reallocx(q->queue, sizeof(int) * q->capacity);
        if (q->front > q->back) {
            for (size_t i = q->front; i < old_capacity; i++) {
                q->queue[i + old_capacity] = q->queue[i];
            }
            q->front = q->front + old_capacity;
        }
    }
    q->back++;
    if (q->back == q->capacity)
        q->back = 0;
    q->queue[q->back] = data;
    q->size++;
}

void queue_pop(queue_t *q) {
    assert(q->size > 0);
    if (q->size == q->capacity / 4 && q->capacity > 4) {
        size_t new_capacity = q->capacity / 2;
        if (q->front <= q->back) {
            for (size_t i = q->front, j = 0; i <= q->back; i++, j++) {
                q->queue[j] = q->queue[i];
            }
        } else {
            size_t front_len = q->capacity - q->front;
            for (int i = q->back; i >= 0; i--) {
                q->queue[i + front_len] = q->queue[i];
            }
            for (size_t i = q->front, j = 0; i < q->capacity; i++, j++) {
                q->queue[j] = q->queue[i];
            }
        }
        q->front = 0;
        q->back = q->size - 1;
        q->capacity = new_capacity;
        q->queue = reallocx(q->queue, q->capacity * sizeof(int));
    }
    q->front++;
    q->size--;
    if (q->front == q->capacity)
        q->front = 0;
}

int queue_front(queue_t *q) {
    assert(q->front < q->capacity);
    return q->queue[q->front];
}

size_t queue_size(queue_t *q) {
    return q->size;
}

bool queue_empty(queue_t *q) {
    return queue_size(q) == 0;
}