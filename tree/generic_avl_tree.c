#include "generic_avl_tree.h"
#include "../utils/alloc.h"
#include <assert.h>

static void
generic_avl_tree_delete_node(generic_avl_node_t *v,
                             generic_avl_tree_element_destructor_fn destructor);
static void generic_avl_tree_delete_helper(generic_avl_tree_t *t,
                                           generic_avl_node_t *v);

static generic_avl_node_t *generic_avl_tree_insert_helper(generic_avl_tree_t *t,
                                                          generic_avl_node_t *v,
                                                          void *data);

static generic_avl_node_t *generic_avl_tree_remove_helper(generic_avl_tree_t *t,
                                                          generic_avl_node_t *v,
                                                          void *data);

static int generic_avl_tree_find_helper(generic_avl_tree_t *t,
                                        generic_avl_node_t *v, void *data);

static void
generic_avl_tree_delete_node(generic_avl_node_t *t,
                             generic_avl_tree_element_destructor_fn destructor);

static generic_avl_node_t *
generic_avl_new_node(void *data,
                     generic_avl_tree_element_constructor_fn constructor);

static size_t generic_avl_node_get_height(generic_avl_node_t *v);

static int generic_avl_node_get_balance(generic_avl_node_t *v);

static generic_avl_node_t *generic_avl_left_rotate(generic_avl_node_t *x);

static generic_avl_node_t *generic_avl_right_rotate(generic_avl_node_t *x);

static size_t generic_avl_calculate_height(generic_avl_node_t *v);

static generic_avl_node_t *
generic_avl_tree_find_rightmost(generic_avl_node_t *v) {
    if (v == NULL || v->right == NULL) {
        return v;
    } else {
        return generic_avl_tree_find_rightmost(v->right);
    }
}

static size_t generic_avl_calculate_height(generic_avl_node_t *v) {
    size_t hl, hr;
    if (v == NULL) {
        return 0;
    }
    hl = generic_avl_node_get_height(v->left);
    hr = generic_avl_node_get_height(v->right);
    return hl > hr ? hl + 1 : hr + 1;
}

/* Executa uma rotação para esquerda.

        x                              y
       / \     Left Rotation          / \
      T1  y   – – – – – – – >        x   T3
         / \                        / \
        T2 T3                      T1 T2
*/
static generic_avl_node_t *generic_avl_left_rotate(generic_avl_node_t *x) {
    assert(x != NULL);
    generic_avl_node_t *y = x->right;
    assert(y != NULL);
    x->right = y->left;
    y->left = x;
    x->height = generic_avl_calculate_height(x);
    y->height = generic_avl_calculate_height(y);
    return y;
}

/* Executa uma rotação para direita.

        y                              x
       / \     Right Rotation         / \
      x   T3   – – – – – – – >       T1  y
     / \                                / \
    T1 T2                              T2 T3
*/
static generic_avl_node_t *generic_avl_right_rotate(generic_avl_node_t *y) {
    assert(y != NULL);
    generic_avl_node_t *x = y->left;
    assert(x != NULL);
    y->left = x->right;
    x->right = y;
    y->height = generic_avl_calculate_height(y);
    x->height = generic_avl_calculate_height(x);
    return x;
}

static size_t generic_avl_node_get_height(generic_avl_node_t *v) {
    if (v == NULL) {
        return 0;
    }
    return v->height;
}

static int generic_avl_node_get_balance(generic_avl_node_t *v) {
    if (v == NULL) {
        return 0;
    }
    return ((int)generic_avl_node_get_height(v->left) -
            generic_avl_node_get_height(v->right));
}

void generic_avl_tree_initialize(
    generic_avl_tree_t **t, generic_avl_tree_element_constructor_fn constructor,
    generic_avl_tree_element_destructor_fn destructor,
    generic_avl_tree_element_compare_fn comparator) {
    (*t) = mallocx(sizeof(generic_avl_tree_t));
    (*t)->root = NULL;
    (*t)->size = 0;
    (*t)->constructor = constructor;
    (*t)->destructor = destructor;
    (*t)->comparator = comparator;
}

void generic_avl_tree_delete(generic_avl_tree_t **t) {
    generic_avl_tree_delete_helper((*t), (*t)->root);
    free(*t);
    (*t) = NULL;
}

static void generic_avl_tree_delete_helper(generic_avl_tree_t *t,
                                           generic_avl_node_t *v) {
    if (v != NULL) {
        generic_avl_tree_delete_helper(t, v->left);
        generic_avl_tree_delete_helper(t, v->right);
        generic_avl_tree_delete_node(v, t->destructor);
    }
}

static void generic_avl_tree_delete_node(
    generic_avl_node_t *t, generic_avl_tree_element_destructor_fn destructor) {
    destructor(t->data);
    free(t);
}

void generic_avl_tree_insert(generic_avl_tree_t *t, void *data) {
    t->root = generic_avl_tree_insert_helper(t, t->root, data);
}

generic_avl_node_t *generic_avl_tree_insert_helper(generic_avl_tree_t *t,
                                                   generic_avl_node_t *v,
                                                   void *data) {
    if (v == NULL) {
        v = generic_avl_new_node(data, t->constructor);
        t->size++;
    } else if (t->comparator(data, v->data) < 0) {
        v->left = generic_avl_tree_insert_helper(t, v->left, data);
    } else {
        v->right = generic_avl_tree_insert_helper(t, v->right, data);
    }
    v->height = generic_avl_calculate_height(v);
    int balance = generic_avl_node_get_balance(v);
    if (balance > 1 && generic_avl_node_get_balance(v->left) >= 0) {
        return generic_avl_right_rotate(v);
    }
    if (balance < -1 && generic_avl_node_get_balance(v->right) <= 0) {
        return generic_avl_left_rotate(v);
    }
    if (balance > 1 && generic_avl_node_get_balance(v->left) < 0) {
        v->left = generic_avl_left_rotate(v->left);
        return generic_avl_right_rotate(v);
    }
    if (balance < -1 && generic_avl_node_get_balance(v->right) > 0) {
        v->right = generic_avl_right_rotate(v->right);
        return generic_avl_left_rotate(v);
    }
    return v;
}

static generic_avl_node_t *
generic_avl_new_node(void *data,
                     generic_avl_tree_element_constructor_fn constructor) {
    generic_avl_node_t *new_node = mallocx(sizeof(generic_avl_node_t));
    new_node->height = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = constructor(data);
    return new_node;
}

void generic_avl_tree_remove(generic_avl_tree_t *t, void *data) {
    t->root = generic_avl_tree_remove_helper(t, t->root, data);
}

generic_avl_node_t *generic_avl_tree_remove_helper(generic_avl_tree_t *t,
                                                   generic_avl_node_t *v,
                                                   void *data) {
    if (v == NULL) {
        return v;
    } else if (t->comparator(data, v->data) < 0) {
        v->left = generic_avl_tree_remove_helper(t, v->left, data);
    } else if (t->comparator(data, v->data) > 0) {
        v->right = generic_avl_tree_remove_helper(t, v->right, data);
    } else { /*remoção do nó*/
        /*caso 1 e caso 2, o nó é uma folha ou só tem um filho. Solução:
         * transplantar*/
        if (v->left == NULL) {
            generic_avl_node_t *tmp = v->right;
            generic_avl_tree_delete_node(v, t->destructor);
            t->size--;
            return tmp;
        } else if (v->right == NULL) {
            generic_avl_node_t *tmp = v->left;
            generic_avl_tree_delete_node(v, t->destructor);
            t->size--;
            return tmp;
        }
        /*caso 3, o nó tem dois filhos: achar o nó antecessor do que
           queremos deletar. Obrigatoriamente este nó é uma folha
           ou tem apenas um filho. Solução: colocar o valor da folha no
           nó atual  e proceder a deletar a folha*/
        else {
            generic_avl_node_t *tmp = generic_avl_tree_find_rightmost(v->left);
            void *swap = v->data;
            v->data = tmp->data;
            tmp->data = swap;
            v->left = generic_avl_tree_remove_helper(t, v->left, tmp->data);
        }
    }
    if (v == NULL) {
        return NULL;
    }
    v->height = generic_avl_calculate_height(v);
    int balance = generic_avl_node_get_balance(v);
    if (balance > 1 && generic_avl_node_get_balance(v->left) >= 0) {
        return generic_avl_right_rotate(v);
    }
    if (balance < -1 && generic_avl_node_get_balance(v->right) <= 0) {
        return generic_avl_left_rotate(v);
    }
    if (balance > 1 && generic_avl_node_get_balance(v->left) < 0) {
        v->left = generic_avl_left_rotate(v->left);
        return generic_avl_right_rotate(v);
    }
    if (balance < -1 && generic_avl_node_get_balance(v->right) > 0) {
        v->right = generic_avl_right_rotate(v->right);
        return generic_avl_left_rotate(v);
    }
    return v;
}

int generic_avl_tree_find(generic_avl_tree_t *t, void *data) {
    return generic_avl_tree_find_helper(t, t->root, data);
}

static int generic_avl_tree_find_helper(generic_avl_tree_t *t,
                                        generic_avl_node_t *v, void *data) {
    if (v == NULL) {
        return 0;
    }
    if (t->comparator(data, v->data) < 0) {
        return generic_avl_tree_find_helper(t, v->left, data);
    } else if (t->comparator(data, v->data) > 0) {
        return generic_avl_tree_find_helper(t, v->right, data);
    }
    return 1;
}

size_t generic_avl_tree_size(generic_avl_tree_t *t) {
    return t->size;
}
