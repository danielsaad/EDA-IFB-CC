#ifndef GENERIC_BST_H_INCLUDED
#define GENERIC_BST_H_INCLUDED

#include <stdlib.h>

typedef void *(*generic_bst_element_constructor_fn)(void *);
typedef void (*generic_bst_element_destructor_fn)(void *);
typedef int (*generic_bst_tree_element_compare_fn)(const void *, const void *);

typedef struct generic_bst_node_t {
    void *data;
    struct generic_bst_node_t *left;
    struct generic_bst_node_t *right;
} generic_bst_node_t;

typedef struct generic_bst_t {
    generic_bst_node_t *root;
    generic_bst_element_constructor_fn constructor;
    generic_bst_element_destructor_fn destructor;
    generic_bst_tree_element_compare_fn comparator;
    size_t size;
} generic_bst_t;

void generic_bst_initialize(generic_bst_t **t,
                            generic_bst_element_constructor_fn constructor,
                            generic_bst_element_destructor_fn destructor,
                            generic_bst_tree_element_compare_fn comparator);

void generic_bst_delete(generic_bst_t **);

void generic_bst_insert(generic_bst_t *t, void *data);
void generic_bst_remove(generic_bst_t *t, void *data);
int generic_bst_find(generic_bst_t *, void *data);
size_t generic_bst_size(generic_bst_t *t);

#endif
