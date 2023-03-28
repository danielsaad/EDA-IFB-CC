#ifndef PRIORITY_QUEUE_H_INCLUDED
#define PRIORITY_QUEUE_H_INCLUDED

#include <stdlib.h>


typedef void* (*priority_queue_element_constructor_fn) (void*);
typedef void (*priority_queue_element_destructor_fn)(void *);
typedef int (*priority_queue_element_compare_fn)(const void*,const void*);


typedef struct priority_queue_t{
    void** data;
    priority_queue_element_constructor_fn constructor;
    priority_queue_element_destructor_fn destructor;
    priority_queue_element_compare_fn comparator;
    size_t size;
    size_t capacity;
}priority_queue_t;

void priority_queue_initialize(priority_queue_t** pq,
                               priority_queue_element_constructor_fn constructor,
                               priority_queue_element_destructor_fn destructor,
                               priority_queue_element_compare_fn comparator);
void priority_queue_delete(priority_queue_t** pq);
void priority_queue_push(priority_queue_t* pq,void* data);
void* priority_queue_front(priority_queue_t* pq);
void priority_queue_pop(priority_queue_t* pq);
size_t priority_queue_size(priority_queue_t* pq);
size_t priority_queue_empty(priority_queue_t* pq);

#endif
