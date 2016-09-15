#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "../Utils/alloc.h"

/**Inicializa a fila**/
void queue_initialize(queue_t** q,queue_node_constructor_fn constructor,
                      queue_node_destructor_fn destructor){
    (*q) = mallocx(sizeof(queue_t));
    (*q)->back = NULL;
    (*q)->front = NULL;
    (*q)->size = 0;
    (*q)->constructor = constructor;
    (*q)->destructor = destructor;
}

void queue_delete(queue_t** q){
    while(!queue_empty(*q)){
        queue_pop(*q);
    }
    free(*q);
    *q = NULL;
}

/**Retira o elemento da frente da fila**/
void queue_pop(queue_t* q){
    assert(!queue_empty(q));
    queue_iterator_t it = q->front;
    if(queue_size(q)==1){
        q->front = NULL;
        q->back = NULL;
    }
    else{
        q->front = q->front->next;
    }
    q->destructor(it->data);
    free(it);
    q->size--;
}

void* queue_front(queue_t* q){
    assert(!queue_empty(q));
    return(q->front->data);
}

void queue_push(queue_t* q,void* data){
    queue_node_t* new_node = mallocx(sizeof(queue_node_t));
    new_node->data = q->constructor(data);
    new_node->next = NULL;
    if(queue_size(q)==0){
        q->front = new_node;
    }
    else{
        q->back->next = new_node;
    }
    q->back = new_node;
    q->size++;
}

size_t queue_size(queue_t* q){
    return(q->size);
}

size_t queue_empty(queue_t *q){
    return queue_size(q)==0 ? 1 : 0;
}
