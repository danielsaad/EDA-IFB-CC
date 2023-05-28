#ifndef GENERIC_PRIORITY_QUEUE_H_INCLUDED
#define GENERIC_PRIORITY_QUEUE_H_INCLUDED

#include <stdlib.h>


typedef void* (*generic_priority_queue_element_constructor_fn) (void*);
typedef void (*generic_priority_queue_element_destructor_fn)(void *);
typedef int (*generic_priority_queue_element_compare_fn)(const void*,const void*);


typedef struct generic_priority_queue_t{
    void** data;
    generic_priority_queue_element_constructor_fn constructor;
    generic_priority_queue_element_destructor_fn destructor;
    generic_priority_queue_element_compare_fn comparator;
    size_t size;
    size_t capacity;
}generic_priority_queue_t;

void generic_priority_queue_initialize(generic_priority_queue_t** pq,
                               generic_priority_queue_element_constructor_fn constructor,
                               generic_priority_queue_element_destructor_fn destructor,
                               generic_priority_queue_element_compare_fn comparator);
void generic_priority_queue_delete(generic_priority_queue_t** pq);
void generic_priority_queue_push(generic_priority_queue_t* pq,void* data);
void* generic_priority_queue_front(generic_priority_queue_t* pq);
void generic_priority_queue_pop(generic_priority_queue_t* pq);
size_t generic_priority_queue_size(generic_priority_queue_t* pq);
size_t generic_priority_queue_empty(generic_priority_queue_t* pq);

#endif
