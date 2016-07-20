#ifndef AVL_TREE_H_INCLUDED
#define AVL_TREE_H_INCLUDED
#include <stdlib.h>

typedef void* (*avl_tree_element_constructor_fn) (void*);
typedef void (*avl_tree_element_destructor_fn)(void *);
typedef int (*avl_tree_element_compare_fn)(const void*,const void*);


typedef struct avl_node_t{
    void* data;
    size_t height;
    struct avl_node_t* left;
    struct avl_node_t* right;
}avl_node_t;


typedef struct avl_tree_t{
    struct avl_node_t* root;
    avl_tree_element_constructor_fn constructor;
    avl_tree_element_destructor_fn destructor;
    avl_tree_element_compare_fn comparator;
    size_t size;
}avl_tree_t;


void avl_tree_initialize(avl_tree_t** t,
                         avl_tree_element_constructor_fn constructor,
                         avl_tree_element_destructor_fn destructor,
                         avl_tree_element_compare_fn comparator);

void avl_tree_delete(avl_tree_t** t);

void avl_tree_insert(avl_tree_t* t,void* data);

void avl_tree_remove(avl_tree_t* t,void* data);

int avl_tree_find(avl_tree_t* t, void* data);

size_t avl_tree_size(avl_tree_t* t);

#endif
