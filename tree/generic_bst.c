#include "generic_bst.h"
#include "../utils/alloc.h"

static generic_bst_node_t *
generic_bst_insert_helper(generic_bst_t *t, generic_bst_node_t *v, void *data);

static void generic_bst_delete_helper(generic_bst_t *t, generic_bst_node_t *v);

static int generic_bst_find_helper(generic_bst_t *t, generic_bst_node_t *v,
                                   void *data);

static generic_bst_node_t *
generic_bst_remove_helper(generic_bst_t *t, generic_bst_node_t *v, void *data);

static generic_bst_node_t *generic_bst_find_rightmost(generic_bst_node_t *v);

static generic_bst_node_t *
generic_bst_new_node(void *data,
                     generic_bst_element_constructor_fn constructor);

static void
generic_bst_delete_node(generic_bst_node_t *node,
                        generic_bst_element_destructor_fn destructor);

static void
generic_bst_delete_node(generic_bst_node_t *node,
                        generic_bst_element_destructor_fn destructor) {
    destructor(node->data);
    free(node);
}

static generic_bst_node_t *
generic_bst_new_node(void *data,
                     generic_bst_element_constructor_fn constructor) {
    generic_bst_node_t *ptr = mallocx(sizeof(generic_bst_node_t));
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->data = constructor(data);
    return ptr;
}

void generic_bst_initialize(generic_bst_t **t,
                            generic_bst_element_constructor_fn constructor,
                            generic_bst_element_destructor_fn destructor,
                            generic_bst_tree_element_compare_fn comparator) {
    (*t) = mallocx(sizeof(generic_bst_t));
    (*t)->root = NULL;
    (*t)->size = 0;
    (*t)->comparator = comparator;
    (*t)->constructor = constructor;
    (*t)->destructor = destructor;
}

void generic_bst_delete(generic_bst_t **t) {
    generic_bst_delete_helper((*t), (*t)->root);
    free(*t);
    (*t) = NULL;
}

static void generic_bst_delete_helper(generic_bst_t *t, generic_bst_node_t *v) {
    if (v != NULL) {
        generic_bst_delete_helper(t, v->left);
        generic_bst_delete_helper(t, v->right);
        generic_bst_delete_node(v, t->destructor);
    }
}

static generic_bst_node_t *generic_bst_find_rightmost(generic_bst_node_t *v) {
    if (v == NULL || v->right == NULL) {
        return v;
    } else {
        return generic_bst_find_rightmost(v->right);
    }
}

void generic_bst_insert(generic_bst_t *t, void *data) {
    t->root = generic_bst_insert_helper(t, t->root, data);
}

static generic_bst_node_t *
generic_bst_insert_helper(generic_bst_t *t, generic_bst_node_t *v, void *data) {
    if (v == NULL) {
        t->size++;
        v = generic_bst_new_node(data, t->constructor);
    } else if (t->comparator(data, v->data) < 0) {
        v->left = generic_bst_insert_helper(t, v->left, data);
    } else {
        v->right = generic_bst_insert_helper(t, v->right, data);
    }
    return v;
}

void generic_bst_remove(generic_bst_t *t, void *data) {
    t->root = generic_bst_remove_helper(t, t->root, data);
}

static generic_bst_node_t *
generic_bst_remove_helper(generic_bst_t *t, generic_bst_node_t *v, void *data) {
    if (v == NULL) {
        return v;
    } else if (t->comparator(data, v->data) < 0) {
        v->left = generic_bst_remove_helper(t, v->left, data);
    } else if (t->comparator(data, v->data) > 0) {
        v->right = generic_bst_remove_helper(t, v->right, data);
    } else { /*remoção do nó*/
        /*caso 1 e caso 2, o nó é uma folha ou só tem um filho. Solução:
         * transplantar*/
        if (v->left == NULL) {
            generic_bst_node_t *tmp = v->right;
            generic_bst_delete_node(v, t->destructor);
            t->size--;
            return tmp;
        } else if (v->right == NULL) {
            generic_bst_node_t *tmp = v->left;
            generic_bst_delete_node(v, t->destructor);
            t->size--;
            return tmp;
        } else {
            /*caso 3, o nó tem dois filhos: devemos o nó antecessor do
             que queremos deletar e realizar o swap.
             Obrigatoriamente este nó cai no caso 1 ou caso 2.*/
            generic_bst_node_t *tmp = generic_bst_find_rightmost(v->left);
            void *swap = v->data;
            v->data = tmp->data;
            tmp->data = swap;
            v->left = generic_bst_remove_helper(t, v->left, tmp->data);
        }
    }
    return v;
}

int generic_bst_find(generic_bst_t *t, void *data) {
    return generic_bst_find_helper(t, t->root, data);
}

static int generic_bst_find_helper(generic_bst_t *t, generic_bst_node_t *v,
                                   void *data) {
    if (v == NULL) {
        return 0;
    }
    if (t->comparator(data, v->data) < 0) {
        return generic_bst_find_helper(t, v->left, data);
    } else if (t->comparator(data, v->data) > 0) {
        return generic_bst_find_helper(t, v->right, data);
    }
    return 1;
}

size_t generic_bst_size(generic_bst_t *t) {
    return t->size;
}
