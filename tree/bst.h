#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <stdbool.h>
#include <stdlib.h>

typedef struct bst_node_t {
    int data;
    struct bst_node_t *left;
    struct bst_node_t *right;
} bst_node_t;

typedef struct bst_t {
    bst_node_t *root;
    size_t size;
} bst_t;

void bst_initialize(bst_t **t);
void bst_delete(bst_t **t);
void bst_insert(bst_t *t, int data);
void bst_remove(bst_t *t, int data);
bool bst_find(bst_t *t, int data);
size_t bst_size(bst_t *t);

#endif
