#include <limits.h>
#include "treap.h"
#include "Utils/alloc.h"


void treap_initialize(treap_t** t,treap_element_constructor_fn constructor,
                      treap_element_destructor_fn destructor,
                      treap_tree_element_compare_fn comparator){
    (*t) = mallocx(sizeof(treap_t));
    (*t)->size = 0;
    (*t)->root = NULL;
    (*t)->constructor = constructor;
    (*t)->destructor = destructor;
    (*t)->comparator = comparator;
}

treap_node_t* treap_new_node(void* data,treap_element_constructor_fn constructor){
    treap_node_t* new_node = mallocx(sizeof(treap_node_t));
    new_node->data = constructor(data);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->rnd = rnd();
    new_node->rnd = new_node->rnd == 0 ? 1 : new_node->rnd;
    return new_node;
}

void treap_delete_node(treap_node_t* v,treap_element_destructor_fn destructor){
    destructor(v->data);
    free(v);
}

void treap_delete(treap_t** t){
    treap_delete_helper((*t),(*t)->root);
}

void treap_delete_helper(treap_t* t,treap_node_t* v){
    if(v!=NULL){
        treap_delete_helper(v->left);
        treap_delete_helper(v->right);
        treap_delete_node(v,t->destructor);
    }
}




/* Performa uma rotação para esquerda.

        x                              y
       / \     Left Rotation          / \
      T1  y   – – – – – – – >        x   T3
         / \                        / \
        T2 T3                      T1 T2
*/
static treap_node_t* treap_left_rotate(treap_node_t* x){
    assert(x!=NULL);
    treap_node_t* y = x->right;
    assert(y!=NULL);
    x->right = y->left;
    y->left = x;
    return y;
}

/* Performa uma rotação para direita.

        y                              x
       / \     Right Rotation         / \
      x   T3   – – – – – – – >       T1  y
     / \                                / \
    T1 T2                              T2 T3
*/
static treap_node_t* treap_right_rotate(treap_node_t* y){
    assert(y!=NULL);
    treap_node_t* x = y->left;
    assert(x!=NULL);
    y->left = x->right;
    x->right = y;
    return x;
}



void treap_insert(treap_t*,void* data){
    t->root = treap_insert_helper(t,t->root,data);
}

void treap_insert_helper(treap_t* t,treap_node_t* v,void* data){
    if(v==NULL){
        return treap_new_node(data,t->constructor);
    }
    else if(t->comparator(data,v->data)<0){
        v->left = treap_insert_helper(t,v->left,data);
    }
    else{
        v->right = treap_insert_helper(t,v->right,data);
    }

    size_t largest_rnd = v->rnd;
    treap_node_t* largest_node = v;
    if(v->left!=NULL && v->left->rnd > largest_rnd_){
        largest_rnd = v->left->rnd;
        largest_node = v->left;
    }
    if(v->right!=NULL && v->right->rnd > largest_rnd){
        largest_rnd = v->right->rnd;
        largest_node = v->right;
    }
    if(largest_node==v->left){
        return treap_rotate_right(v);
    }
    else if(largest_node==v->right){
        return treap_rotate_left(v);
    }
    return v;

}

void treap_remove(treap_t* t,void* data){
    t->root = treap_remove_helper(t,t->root,data);
}

treap_node_t treap_restore_property(treap_node_t* v){
    size_t largest_rnd =  v->rnd;
    treap_node_t* largest_node = v;
    if(v->left!=NULL && v->left->rnd > largest_rnd){
        largest_rnd = v->left->rnd;
        largest_node = v->left;
    }
    if(v->right!=NULL && v->right->rnd > largest_rnd){
        largest_rnd = v->right->rnd;
        largest_node = v->right;
    }
    if(largest_node==v->left){
        treap_right_rotate(v);
        return(treap_restore_property(v->right));
    }
    else if(largest_node==v->right){
        treap_left_rotate(v);
        return(treap_restore_property(v->left));
    }
    return v;
}

treap_node_t* treap_remove_helper(treap_t* t,treap_node_t* v,void* data){
    if(v==NULL){
        return v;
    }
    else if(t->comparator(data,v->data)<0){
        v->left = treap_remove_helper(t,v->left,data);
    }
    else if(t->comparator(data,v->data)>0){
        v->right = treap_remove_helper(t,v->right,data);
    }
    else{
        v->rnd = 0;
        v = restore_treap_property(v);
        treap_delete_node(v);
        v = NULL;
    }
    return v;
}

int treap_find(treap_t*,void* data){
    return treap_find_helper(t,t->root,data);
}

treap_node_t* treap_find_helper(treap_t* t,treap_node_t* v,void* data){
    if(v==NULL){
        return 0;
    }
    else if(t->comparator(data,v->data)<0){
        return treap_find_helper(t,v->left,data);
    }
    else if(t->comparator(data,v->data)>0){
        return treap_find_helper(t,v->right,data);
    }
    return 1;
}

size_t treap_size(treap_t* t){
    return t->size;
}
