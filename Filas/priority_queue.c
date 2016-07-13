#include <assert.h>
#include "priority_queue.h"
#include "../Utils/alloc.h"


static void priority_queue_heapify_bottom_up(priority_queue_t* pq,size_t i){
    size_t p;
    for(p=i/2;i!=0;p=p/2){
        if(pq->comparator(pq->data[i],pq->data[p]>0)){
            break;
        }
        void* aux = pq->data[i];
        pq->data[i] = pq->data[p];
        pq->data[p] = aux;
        i = p;
    }
}


static void priority_queue_heapify_top_down(priority_queue_t* pq,size_t i){
    size_t l,r;
    size_t smallest;
    while(i<priority_queue_size(pq)){
        smallest = i;
        l = 2*i +1;
        r = 2*i +2;
        if(l<priority_queue_size(pq) && pq->comparator(pq->data[i],pq->data[l])>0){
            smallest = l;
        }
        if(r<priority_queue_size(pq) && pq->comparator(pq->data[smallest],pq->data[r])>0){
            smallest = r;
        }
        if(smallest==i){
            break;
        }
    }
}

void priority_queue_initialize(priority_queue_t** pq, priority_queue_compare_fn comparator,
                               priority_queue_element_constructor_fn constructor,
                               priority_queue_element_destructor_fn destructor){
    (*pq) = mallocx(sizeof(priority_queue_t));
    (*pq)->data = NULL;
    (*pq)->comparator = comparator;
    (*pq)->constructor = constructor;
    (*pq)->destructor = destructor;
    (*pq)->size = 0;
    (*pq)->capacity = 0;
}

void priority_queue_delete(priority_queue_t** pq){
    while(!priority_queue_empty(*pq)){
        priority_queue_pop(*pq);
    }
    free(*pq);
    *pq = NULL;
}

void priority_queue_push(priority_queue_t* pq,void* data){
    if(pq->size == pq->capacity){
        if(pq->capacity == 0){
            pq->capacity = 1;
        }
        else{
            pq->capacity*=2;
        }
        pq->data = reallocx(pq->data,pq->capacity);
    }
    pq->data[pq->size] = pq->constructor(data);
    priority_queue_heapify_bottom_up(pq,pq->size);
    pq->size++;
}

void* priority_queue_front(priority_queue_t* pq){
    assert(!priority_queue_empty(pq));
    return(pq->data[0]);
}

void priority_queue_pop(priority_queue_t* pq){
    assert(!priority_queue_empty(pq));
    pq->size--;
    pq->destructor(pq->data[pq->size]);
    if(pq->size == pq->capacity/2){
        pq->data = reallocx(pq->data,pq->capacity/2);
    }
    if(!priority_queue_empty(pq)){
        void* aux = pq->data[pq->size-1];
        pq->data[pq->size-1] = pq->data[0];
        pq->data[0] = aux;
        priority_queue_heapify_bottom_up(pq,0);
    }
}

size_t priority_queue_size(priority_queue_t* pq){
    return pq->size;
}

size_t priority_queue_empty(priority_queue_t* pq){
    return priority_queue_size(pq) == 0 ? 1: 0;
}
