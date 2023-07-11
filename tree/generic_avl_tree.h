#ifndef GENERIC_AVL_TREE_H_INCLUDED
#define GENERIC_AVL_TREE_H_INCLUDED
#include <stdlib.h>

typedef void *(*generic_avl_tree_element_constructor_fn)(void *);
typedef void (*generic_avl_tree_element_destructor_fn)(void *);
typedef int (*generic_avl_tree_element_compare_fn)(const void *, const void *);

typedef struct generic_avl_node_t {
    void *data;
    size_t height;
    struct generic_avl_node_t *left;
    struct generic_avl_node_t *right;
} generic_avl_node_t;

typedef struct generic_avl_tree_t {
    struct generic_avl_node_t *root;
    generic_avl_tree_element_constructor_fn constructor;
    generic_avl_tree_element_destructor_fn destructor;
    generic_avl_tree_element_compare_fn comparator;
    size_t size;
} generic_avl_tree_t;

void generic_avl_tree_initialize(
    generic_avl_tree_t **t, generic_avl_tree_element_constructor_fn constructor,
    generic_avl_tree_element_destructor_fn destructor,
    generic_avl_tree_element_compare_fn comparator);

void generic_avl_tree_delete(generic_avl_tree_t **t);

void generic_avl_tree_insert(generic_avl_tree_t *t, void *data);

void generic_avl_tree_remove(generic_avl_tree_t *t, void *data);

int generic_avl_tree_find(generic_avl_tree_t *t, void *data);

size_t generic_avl_tree_size(generic_avl_tree_t *t);

#endif
