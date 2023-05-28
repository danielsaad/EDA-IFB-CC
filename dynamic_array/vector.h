#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdlib.h>

typedef void* (*vector_element_constructor_fn) (void*);
typedef void (*vector_element_destructor_fn)(void *);

typedef struct vector{
    void** data;
    vector_element_constructor_fn constructor;
    vector_element_destructor_fn destructor;
    size_t size;
    size_t capacity;
}vector;

void vector_initialize(vector** v,vector_element_constructor_fn constructor,
                       vector_element_destructor_fn destructor);
void vector_delete(vector** v);
void* vector_access(vector* v,size_t i);
void vector_push_back(vector* v,void* data);
void vector_pop_back(vector* v);
size_t vector_size(vector* v);
size_t vector_empty(vector* v);

#endif
