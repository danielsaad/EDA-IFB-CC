#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <stdlib.h>

typedef void* (*bst_element_constructor_fn) (void*);
typedef void (*bst_element_destructor_fn)(void *);
typedef int (*bst_tree_element_compare_fn)(const void*,const void*);


typedef struct bst_node_t{
    void* data;
    struct bst_node_t* left;
    struct bst_node_t* right;
}bst_node_t;


typedef struct bst_t{
    bst_node_t* root;
    bst_element_constructor_fn constructor;
    bst_element_destructor_fn destructor;
    bst_tree_element_compare_fn comparator;
    size_t size;
}bst_t;

void bst_initialize(bst_t** t,
                    bst_element_constructor_fn constructor,
                    bst_element_destructor_fn destructor,
                    bst_tree_element_compare_fn comparator);

void bst_delete(bst_t**);

void bst_insert(bst_t* t,void* data);
void bst_remove(bst_t* t,void* data);
int bst_find(bst_t*, void* data);
size_t bst_size(bst_t* t);

#endif
