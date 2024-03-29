#include "generic_priority_queue.h"
#include "../utils/alloc.h"
#include <assert.h>

static void
generic_priority_queue_heapify_bottom_up(generic_priority_queue_t *pq,
                                         size_t i) {
    size_t p;
    for (p = (i - 1) / 2; i != 0; p = (p - 1) / 2) {
        if (pq->comparator(pq->data[i], pq->data[p]) <= 0) {
            break;
        }
        void *aux = pq->data[i];
        pq->data[i] = pq->data[p];
        pq->data[p] = aux;
        i = p;
    }
}

static void
generic_priority_queue_heapify_top_down(generic_priority_queue_t *pq,
                                        size_t i) {
    size_t l, r;
    size_t largest = i;
    while (i < generic_priority_queue_size(pq)) {
        i = largest;
        l = 2 * i + 1;
        r = 2 * i + 2;
        if (l < generic_priority_queue_size(pq) &&
            pq->comparator(pq->data[i], pq->data[l]) <= 0) {
            largest = l;
        }
        if (r < generic_priority_queue_size(pq) &&
            pq->comparator(pq->data[largest], pq->data[r]) < 0) {
            largest = r;
        }
        if (largest == i) {
            break;
        }
        void *aux = pq->data[i];
        pq->data[i] = pq->data[largest];
        pq->data[largest] = aux;
    }
}

void generic_priority_queue_initialize(
    generic_priority_queue_t **pq,
    generic_priority_queue_element_constructor_fn constructor,
    generic_priority_queue_element_destructor_fn destructor,
    generic_priority_queue_element_compare_fn comparator) {
    (*pq) = mallocx(sizeof(generic_priority_queue_t));
    (*pq)->data = NULL;
    (*pq)->constructor = constructor;
    (*pq)->destructor = destructor;
    (*pq)->comparator = comparator;
    (*pq)->size = 0;
    (*pq)->capacity = 0;
}

void generic_priority_queue_delete(generic_priority_queue_t **pq) {
    while (!generic_priority_queue_empty(*pq)) {
        generic_priority_queue_pop(*pq);
    }
    free(*pq);
    *pq = NULL;
}

void generic_priority_queue_push(generic_priority_queue_t *pq, void *data) {
    if (pq->size == pq->capacity) {
        if (pq->capacity == 0) {
            pq->capacity = 1;
        } else {
            pq->capacity *= 2;
        }
        pq->data = reallocx(pq->data, pq->capacity * sizeof(void *));
    }
    pq->data[pq->size] = pq->constructor(data);
    generic_priority_queue_heapify_bottom_up(pq, pq->size);
    pq->size++;
}

void *generic_priority_queue_front(generic_priority_queue_t *pq) {
    assert(!generic_priority_queue_empty(pq));
    return (pq->data[0]);
}

void generic_priority_queue_pop(generic_priority_queue_t *pq) {
    assert(!generic_priority_queue_empty(pq));
    pq->size--;
    pq->destructor(pq->data[0]);
    if (!generic_priority_queue_empty(pq)) {
        pq->data[0] = pq->data[pq->size];
        generic_priority_queue_heapify_top_down(pq, 0);
    }
    if (pq->size == pq->capacity / 2) {
        pq->data = reallocx(pq->data, pq->capacity / 2 * sizeof(void *));
        pq->capacity = pq->capacity / 2;
    }
}

size_t generic_priority_queue_size(generic_priority_queue_t *pq) {
    return pq->size;
}

size_t generic_priority_queue_empty(generic_priority_queue_t *pq) {
    return generic_priority_queue_size(pq) == 0 ? 1 : 0;
}
