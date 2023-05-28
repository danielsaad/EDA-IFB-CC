#include "../utils/alloc.h"
#include "generic_queue.h"
#include <assert.h>
#include <stdlib.h>

/**Inicializa a fila**/
void generic_queue_initialize(generic_queue_t **q,
                              generic_queue_node_constructor_fn constructor,
                              generic_queue_node_destructor_fn destructor) {
    (*q) = mallocx(sizeof(generic_queue_t));
    (*q)->back = NULL;
    (*q)->front = NULL;
    (*q)->size = 0;
    (*q)->constructor = constructor;
    (*q)->destructor = destructor;
}

void generic_queue_delete(generic_queue_t **q) {
    while (!generic_queue_empty(*q)) {
        generic_queue_pop(*q);
    }
    free(*q);
    *q = NULL;
}

/**Retira o elemento da frente da fila**/
void generic_queue_pop(generic_queue_t *q) {
    assert(!generic_queue_empty(q));
    generic_queue_iterator_t it = q->front;
    if (generic_queue_size(q) == 1) {
        q->front = NULL;
        q->back = NULL;
    } else {
        q->front = q->front->next;
    }
    q->destructor(it->data);
    free(it);
    q->size--;
}

void *generic_queue_front(generic_queue_t *q) {
    assert(!generic_queue_empty(q));
    return (q->front->data);
}

void generic_queue_push(generic_queue_t *q, void *data) {
    generic_queue_node_t *new_node = mallocx(sizeof(generic_queue_node_t));
    new_node->data = q->constructor(data);
    new_node->next = NULL;
    if (generic_queue_size(q) == 0) {
        q->front = new_node;
    } else {
        q->back->next = new_node;
    }
    q->back = new_node;
    q->size++;
}

size_t generic_queue_size(generic_queue_t *q) {
    return (q->size);
}

size_t generic_queue_empty(generic_queue_t *q) {
    return generic_queue_size(q) == 0 ? 1 : 0;
}
