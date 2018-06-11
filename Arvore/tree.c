#include "tree.h"
#include "../Utils/alloc.h"



void tree_initialize(tree_t** t, 
    tree_constructor_fn constructor,tree_destructor_fn destructor, tree_comparator_fn comparator) {

    *t  = mallocx(sizeof(tree_t));
    (*t)->constructor = constructor;
    (*t)->destructor = destructor;
    (*t)->comparator = comparator;
    (*t)->root = NULL;
}


void tree_delete(tree_t** t){
    tree_delete_helper(*t,(*t)->root);
    free(*t);
    *t = NULL;
}

static void tree_delete_helper(tree_t* t,tree_node_t* node){
    if(node != NULL){
        tree_delete_helper(node->left);
        tree_delete_helper(node->right);
        t->destructor(node->data);
        free(node);
    }
}