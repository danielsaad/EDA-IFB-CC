#include "avl_tree.h"
#include "../utils/alloc.h"
#include <assert.h>

static void avl_tree_delete_node(avl_node_t *v);
static void avl_tree_delete_helper(avl_node_t *v);

static avl_node_t *avl_tree_insert_helper(avl_node_t *v, int data);

static avl_node_t *avl_tree_remove_helper(avl_tree_t *t, avl_node_t *v,
                                          int data);

static int avl_tree_find_helper(avl_node_t *v, int data);

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

void avl_tree_insert(avl_tree_t *t, void *data) {
    t->root = avl_tree_insert_helper(t->root, data);
    t->size++;
}

avl_node_t *avl_tree_insert_helper(avl_node_t *v, int data) {
    if (v == NULL) {
        v = avl_new_node(data);
    } else if (data < v->data < 0) {
        v->left = avl_tree_insert_helper(t, v->left, data);
    } else {
        v->right = avl_tree_insert_helper(t, v->right, data);
    }
    v->height = avl_calculate_height(v);
    int balance = avl_node_get_balance(v);
    if (balance > 1 && avl_node_get_balance(v->left) >= 0) {
        return avl_right_rotate(v);
    }
    if (balance < -1 && avl_node_get_balance(v->right) <= 0) {
        return avl_left_rotate(v);
    }
    if (balance > 1 && avl_node_get_balance(v->left) < 0) {
        v->left = avl_left_rotate(v->left);
        return avl_right_rotate(v);
    }
    if (balance < -1 && avl_node_get_balance(v->right) > 0) {
        v->right = avl_right_rotate(v->right);
        return avl_left_rotate(v);
    }
    return v;
}

static avl_node_t *avl_new_node(void *data,
                                avl_tree_element_constructor_fn constructor) {
    avl_node_t *new_node = mallocx(sizeof(avl_node_t));
    new_node->height = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = constructor(data);
    return new_node;
}

void avl_tree_remove(avl_tree_t *t, void *data) {
    t->root = avl_tree_remove_helper(t, t->root, data);
}

avl_node_t *avl_tree_remove_helper(avl_tree_t *t, avl_node_t *v, void *data) {
    if (v == NULL) {
        return v;
    } else if (t->comparator(data, v->data) < 0) {
        v->left = avl_tree_remove_helper(t, v->left, data);
    } else if (t->comparator(data, v->data) > 0) {
        v->right = avl_tree_remove_helper(t, v->right, data);
    } else { /*remoção do nó*/
        /*caso 1 e caso 2, o nó é uma folha ou só tem um filho. Solução:
         * transplantar*/
        if (v->left == NULL) {
            avl_node_t *tmp = v->right;
            avl_tree_delete_node(v, t->destructor);
            t->size--;
            return tmp;
        } else if (v->right == NULL) {
            avl_node_t *tmp = v->left;
            avl_tree_delete_node(v, t->destructor);
            t->size--;
            return tmp;
        }
        /*caso 3, o nó tem dois filhos: achar o nó antecessor do que
           queremos deletar. Obrigatoriamente este nó é uma folha
           ou tem apenas um filho. Solução: colocar o valor da folha no
           nó atual  e proceder a deletar a folha*/
        else {
            avl_node_t *tmp = avl_tree_find_rightmost(v->left);
            void *swap = v->data;
            v->data = tmp->data;
            tmp->data = swap;
            v->left = avl_tree_remove_helper(t, v->left, tmp->data);
        }
    }
    if (v == NULL) {
        return NULL;
    }
    v->height = avl_calculate_height(v);
    int balance = avl_node_get_balance(v);
    if (balance > 1 && avl_node_get_balance(v->left) >= 0) {
        return avl_right_rotate(v);
    }
    if (balance < -1 && avl_node_get_balance(v->right) <= 0) {
        return avl_left_rotate(v);
    }
    if (balance > 1 && avl_node_get_balance(v->left) < 0) {
        v->left = avl_left_rotate(v->left);
        return avl_right_rotate(v);
    }
    if (balance < -1 && avl_node_get_balance(v->right) > 0) {
        v->right = avl_right_rotate(v->right);
        return avl_left_rotate(v);
    }
    return v;
}

int avl_tree_find(avl_tree_t *t, void *data) {
    return avl_tree_find_helper(t, t->root, data);
}

static int avl_tree_find_helper(avl_tree_t *t, avl_node_t *v, void *data) {
    if (v == NULL) {
        return 0;
    }
    if (t->comparator(data, v->data) < 0) {
        return avl_tree_find_helper(t, v->left, data);
    } else if (t->comparator(data, v->data) > 0) {
        return avl_tree_find_helper(t, v->right, data);
    }
    return 1;
}

size_t avl_tree_size(avl_tree_t *t) {
    return t->size;
}
