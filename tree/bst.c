#include "bst.h"
#include "../utils/alloc.h"
#include <assert.h>

static bst_node_t *bst_insert_helper(bst_node_t *v, int data);
static void bst_delete_helper(bst_node_t *v);
static bool bst_find_helper(bst_node_t *v, int data);
static bst_node_t *bst_remove_helper(bst_node_t *v, int data);
static bst_node_t *bst_find_rightmost(bst_node_t *v);
static bst_node_t *bst_new_node(int data);
static void bst_delete_node(bst_node_t *node);

static void bst_delete_node(bst_node_t *node) {
    free(node);
}

static bst_node_t *bst_new_node(int data) {
    bst_node_t *ptr = mallocx(sizeof(bst_node_t));
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->data = data;
    return ptr;
}

static bst_node_t *bst_find_rightmost(bst_node_t *v) {
    if (v == NULL || v->right == NULL) {
        return v;
    } else {
        return bst_find_rightmost(v->right);
    }
}

void bst_initialize(bst_t **t) {
    (*t) = mallocx(sizeof(bst_t));
    (*t)->size = 0;
    (*t)->root = NULL;
}
void bst_delete(bst_t **t) {
    bst_delete_helper((*t)->root);
    (*t)->root = NULL;
}

static void bst_delete_helper(bst_node_t *x) {
    if (x != NULL) {
        bst_delete_helper(x->left);
        bst_delete_helper(x->right);
        bst_delete_node(x);
    }
}

void bst_insert(bst_t *t, int data) {
    t->root = bst_insert_helper(t->root, data);
    t->size++;
}

bst_node_t *bst_insert_helper(bst_node_t *x, int data) {
    if (x == NULL)
        return bst_new_node(data);
    assert(x->data != data);
    if (data < x->data) {
        x->left = bst_insert_helper(x->left, data);
    } else {
        x->right = bst_insert_helper(x->right, data);
    }
    return x;
}

void bst_remove(bst_t *t, int data) {
    t->root = bst_remove_helper(t->root, data);
    t->size--;
}

static bst_node_t *bst_remove_helper(bst_node_t *x, int data) {
    assert(x != NULL);
    if (data < x->data)
        x->left = bst_remove_helper(x->left, data);
    else if (data > x->data) {
        x->right = bst_remove_helper(x->right, data);
    } else {
        if (x->left == NULL) {
            bst_node_t *y = x->right;
            bst_delete_node(x);
            x = y;
        } else if (x->right == NULL) {
            bst_node_t *y = x->left;
            bst_delete_node(x);
            x = y;
        } else {
            bst_node_t *previous_x = bst_find_rightmost(x->left);
            int aux = x->data;
            x->data = previous_x->data;
            previous_x->data = aux;
            x->left = bst_remove_helper(x->left, data);
        }
    }
    return x;
}

bool bst_find(bst_t *t, int data) {
    return bst_find_helper(t->root, data);
}

static bool bst_find_helper(bst_node_t *x, int data) {
    if (x == NULL)
        return false;
    if (data == x->data)
        return true;
    if (data < x->data)
        return bst_find_helper(x->left, data);
    return bst_find_helper(x->right, data);
}

size_t bst_size(bst_t *t) {
    return t->size;
}
