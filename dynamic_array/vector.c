#include <assert.h>
#include "vector.h"
#include "../utils/alloc.h"

void vector_initialize(vector** v,vector_element_constructor_fn constructor,
                       vector_element_destructor_fn destructor){
    (*v) = mallocx(sizeof(vector));
    (*v)->data = NULL;
    (*v)->constructor = constructor;
    (*v)->destructor = destructor;
    (*v)->size = 0;
    (*v)->capacity = 0;
}

void vector_delete(vector** v){
    while(!vector_empty(*v)){
        vector_pop_back(*v);
    }
    free(*v);
    (*v) = NULL;
}

void* vector_access(vector* v,size_t i){
    assert(i<vector_size(v));
    return(v->data[i]);
}

void vector_push_back(vector* v,void* data){
    if(v->size == v->capacity){
        if(v->capacity == 0){
            v->capacity = 1;
        }
        else{
            v->capacity*=2;
        }
        v->data = reallocx(v->data,v->capacity);
    }
    v->data[v->size] = v->constructor(data);
    v->size++;
}

void vector_pop_back(vector* v){
    assert(!vector_empty(v));
    v->size--;
    v->destructor(v->data[v->size]);
    if(v->size == v->capacity/2){
        v->data = reallocx(v->data,v->capacity/2);
    }
}

size_t vector_size(vector* v){
    return v->size;
}

size_t vector_empty(vector* v){
    return vector_size(v) == 0 ? 1 : 0;
}
