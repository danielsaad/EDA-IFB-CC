#include "deque.h"
#include "../utils/alloc.h"
#include <assert.h>

static void deque_expand(deque_t *d);
static void deque_shrink(deque_t *d);

static void deque_expand(deque_t *d) {
    size_t old_capacity = d->capacity;
    d->capacity *= 2;
    d->deque = reallocx(d->deque, sizeof(int) * d->capacity);
    if (d->front > d->back) {
        for (size_t i = d->front; i < old_capacity; i++) {
            d->deque[i + old_capacity] = d->deque[i];
        }
        d->front = d->front + old_capacity;
    }
}

static void deque_shrink(deque_t *d) {
    size_t new_capacity = d->capacity / 2;
    if (d->front <= d->back) {
        for (size_t i = d->front, j = 0; i <= d->back; i++, j++) {
            d->deque[j] = d->deque[i];
        }
    } else {
        size_t front_len = d->capacity - d->front;
        for (int i = d->back; i >= 0; i--) {
            d->deque[i + front_len] = d->deque[i];
        }
        for (size_t i = d->front, j = 0; i < d->capacity; i++, j++) {
            d->deque[j] = d->deque[i];
        }
    }
    d->front = 0;
    d->back = d->size - 1;
    d->capacity = new_capacity;
    d->deque = reallocx(d->deque, d->capacity * sizeof(int));
}

void deque_initialize(deque_t **d) {
    (*d) = mallocx(sizeof(deque_t));
    (*d)->front = 0;
    (*d)->back = 3;
    (*d)->size = 0;
    (*d)->capacity = 4;
    (*d)->deque = mallocx(sizeof(int) * 4);
}

void deque_delete(deque_t **d) {
    free((*d)->deque);
    free(*d);
    *d = NULL;
}

void deque_push_back(deque_t *d, int data) {
    if (d->size == d->capacity) {
        deque_expand(d);
    }
    d->back++;
    if (d->back == d->capacity)
        d->back = 0;
    d->deque[d->back] = data;
    d->size++;
}

void deque_push_front(deque_t *d, int data) {
    if (d->size == d->capacity) {
        deque_expand(d);
    }
    d->front = d->front == 0 ? d->capacity - 1 : d->front - 1;
    d->deque[d->front] = data;
    d->size++;
}

void deque_pop_front(deque_t *d) {
    assert(d->size > 0);
    if (d->size == d->capacity / 4 && d->capacity > 4) {
        deque_shrink(d);
    }
    d->front++;
    d->size--;
    if (d->front == d->capacity)
        d->front = 0;
}

void deque_pop_back(deque_t *d) {
    if (d->size == d->capacity / 4 && d->capacity > 4) {
        deque_shrink(d);
    }
    assert(d->size > 0);
    d->back = d->back == 0 ? d->capacity - 1 : d->back - 1;
    d->size--;
}

int deque_front(deque_t *d) {
    assert(d->front < d->capacity);
    return d->deque[d->front];
}

int deque_back(deque_t *d) {
    assert(d->front < d->capacity);
    return d->deque[d->back];
}

size_t deque_size(deque_t *d) {
    return d->size;
}

bool deque_empty(deque_t *d) {
    return deque_size(d) == 0;
}