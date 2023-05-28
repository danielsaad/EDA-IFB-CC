#ifndef TREAP_H_INCLUDED
#define TREAP_H_INCLUDED
#include <stdlib.h>

typedef void* (*treap_element_constructor_fn) (void*);
typedef void (*treap_element_destructor_fn)(void *);
typedef int (*treap_tree_element_compare_fn)(const void*,const void*);


typedef struct treap_node_t{
    size_t priority;
    void* data;
    struct treap_node_t* left;
    struct treap_node_t* right;
}treap_node_t;


typedef struct treap_t{
    treap_node_t* root;
    size_t size;
    treap_element_constructor_fn constructor;
    treap_element_destructor_fn destructor;
    treap_tree_element_compare_fn comparator;
}treap_t;


void treap_initialize(treap_t** t,treap_element_constructor_fn constructor,
                      treap_element_destructor_fn destructor,
                      treap_tree_element_compare_fn comparator);

void treap_delete(treap_t**);

void treap_insert(treap_t*,void* data);

void treap_remove(treap_t*,void* data);

int treap_find(treap_t*,void* data);

size_t treap_size(treap_t*);

#endif
