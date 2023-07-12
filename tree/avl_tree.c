#include "avl_tree.h"
#include "../utils/alloc.h"
#include <assert.h>

static void avl_tree_delete_node(avl_node_t *v);
static void avl_tree_delete_helper(avl_node_t *v);

static avl_node_t *balance(avl_node_t *v);

static avl_node_t *avl_tree_insert_helper(avl_node_t *v, int data);

static avl_node_t *avl_tree_remove_helper(avl_node_t *v, int data);

static bool avl_tree_find_helper(avl_node_t *v, int data);

static void avl_tree_delete_node(avl_node_t *v);

static avl_node_t *avl_new_node(int data);

static size_t avl_node_get_height(avl_node_t *v);

static int avl_node_get_balance(avl_node_t *v);

static avl_node_t *avl_left_rotate(avl_node_t *x);

static avl_node_t *avl_right_rotate(avl_node_t *x);

static size_t avl_calculate_height(avl_node_t *v);

static avl_node_t *avl_tree_find_rightmost(avl_node_t *v) {
    if (v == NULL || v->right == NULL) {
        return v;
    } else {
        return avl_tree_find_rightmost(v->right);
    }
}

static size_t avl_calculate_height(avl_node_t *v) {
    size_t hl, hr;
    if (v == NULL) {
        return 0;
    }
    hl = avl_node_get_height(v->left);
    hr = avl_node_get_height(v->right);
    return hl > hr ? hl + 1 : hr + 1;
}

/* Executa uma rotação para esquerda.

        x                              y
       / \     Left Rotation          / \
      T1  y   – – – – – – – >        x   T3
         / \                        / \
        T2 T3                      T1 T2
*/
static avl_node_t *avl_left_rotate(avl_node_t *x) {
    assert(x != NULL);
    avl_node_t *y = x->right;
    assert(y != NULL);
    x->right = y->left;
    y->left = x;
    x->height = avl_calculate_height(x);
    y->height = avl_calculate_height(y);
    return y;
}

/* Executa uma rotação para direita.

        y                              x
       / \     Right Rotation         / \
      x   T3   – – – – – – – >       T1  y
     / \                                / \
    T1 T2                              T2 T3
*/
static avl_node_t *avl_right_rotate(avl_node_t *y) {
    assert(y != NULL);
    avl_node_t *x = y->left;
    assert(x != NULL);
    y->left = x->right;
    x->right = y;
    y->height = avl_calculate_height(y);
    x->height = avl_calculate_height(x);
    return x;
}

static size_t avl_node_get_height(avl_node_t *v) {
    if (v == NULL) {
        return 0;
    }
    return v->height;
}

static int avl_node_get_balance(avl_node_t *v) {
    if (v == NULL) {
        return 0;
    }
    return ((int)avl_node_get_height(v->left) - avl_node_get_height(v->right));
}

static avl_node_t *balance(avl_node_t *v) {
    int balance = avl_node_get_balance(v);
    if (balance > 1 && avl_node_get_balance(v->left) >= 0) {
        v = avl_right_rotate(v);
    } else if (balance < -1 && avl_node_get_balance(v->right) <= 0) {
        v = avl_left_rotate(v);
    } else if (balance > 1 && avl_node_get_balance(v->left) < 0) {
        v->left = avl_left_rotate(v->left);
        v = avl_right_rotate(v);
    } else if (balance < -1 && avl_node_get_balance(v->right) > 0) {
        v->right = avl_right_rotate(v->right);
        v = avl_left_rotate(v);
    }
    return v;
}

void avl_tree_initialize(avl_tree_t **t) {
    (*t) = mallocx(sizeof(avl_tree_t));
    (*t)->root = NULL;
    (*t)->size = 0;
}

void avl_tree_delete(avl_tree_t **t) {
    avl_tree_delete_helper((*t)->root);
    free(*t);
    (*t) = NULL;
}

static void avl_tree_delete_helper(avl_node_t *v) {
    if (v != NULL) {
        avl_tree_delete_helper(v->left);
        avl_tree_delete_helper(v->right);
        avl_tree_delete_node(v);
    }
}

static void avl_tree_delete_node(avl_node_t *t) {
    free(t);
}

void avl_tree_insert(avl_tree_t *t, int data) {
    t->root = avl_tree_insert_helper(t->root, data);
    t->size++;
}

avl_node_t *avl_tree_insert_helper(avl_node_t *v, int data) {
    if (v == NULL) {
        v = avl_new_node(data);
        v->height = avl_calculate_height(v);
        return v;
    }
    assert(v->data != data);
    if (data < v->data) {
        v->left = avl_tree_insert_helper(v->left, data);
    } else {
        v->right = avl_tree_insert_helper(v->right, data);
    }
    v->height = avl_calculate_height(v);
    v = balance(v);
    return v;
}

static avl_node_t *avl_new_node(int data) {
    avl_node_t *new_node = mallocx(sizeof(avl_node_t));
    new_node->height = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = data;
    return new_node;
}

void avl_tree_remove(avl_tree_t *t, int data) {
    t->root = avl_tree_remove_helper(t->root, data);
    t->size--;
}

avl_node_t *avl_tree_remove_helper(avl_node_t *v, int data) {
    assert(v != NULL);
    if (data < v->data) {
        v->left = avl_tree_remove_helper(v->left, data);
    } else if (data > v->data) {
        v->right = avl_tree_remove_helper(v->right, data);
    } else { /*remoção do nó*/
        if (v->left == NULL) {
            avl_node_t *tmp = v->right;
            avl_tree_delete_node(v);
            return tmp;
        } else if (v->right == NULL) {
            avl_node_t *tmp = v->left;
            avl_tree_delete_node(v);
            return tmp;
        } else {
            avl_node_t *previous_v = avl_tree_find_rightmost(v->left);
            int aux = v->data;
            v->data = previous_v->data;
            previous_v->data = aux;
            v->left = avl_tree_remove_helper(v->left, previous_v->data);
        }
    }
    if (v != NULL) {
        v->height = avl_calculate_height(v);
        v = balance(v);
    }
    return v;
}

bool avl_tree_find(avl_tree_t *t, int data) {
    return avl_tree_find_helper(t->root, data);
}

static bool avl_tree_find_helper(avl_node_t *v, int data) {
    if (v == NULL) {
        return false;
    }
    if (data < v->data) {
        return avl_tree_find_helper(v->left, data);
    } else if (data > v->data) {
        return avl_tree_find_helper(v->right, data);
    }
    return true;
}

size_t avl_tree_size(avl_tree_t *t) {
    return t->size;
}
