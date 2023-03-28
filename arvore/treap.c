#include <limits.h>
#include <time.h>
#include <assert.h>
#include "treap.h"
#include "../utils/alloc.h"

static treap_node_t* treap_new_node(void* data,treap_element_constructor_fn constructor);
static void treap_delete_node(treap_node_t* v,treap_element_destructor_fn destructor);
static void treap_delete_helper(treap_t* t,treap_node_t* v);
static treap_node_t* treap_left_rotate(treap_node_t* x);
static treap_node_t* treap_right_rotate(treap_node_t* y);
static treap_node_t* treap_insert_helper(treap_t* t,treap_node_t* v,void* data);
static treap_node_t* treap_remove_helper(treap_t* t,treap_node_t* v,void* data);
static int treap_find_helper(treap_t* t,treap_node_t* v,void* data);

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

static treap_node_t* treap_new_node(void* data,treap_element_constructor_fn constructor){
    treap_node_t* new_node = mallocx(sizeof(treap_node_t));
    new_node->data = constructor(data);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->priority = rand();
    new_node->priority = new_node->priority == 0 ? 1 : new_node->priority;
    srand(time(NULL));
    return new_node;
}

static void treap_delete_node(treap_node_t* v,treap_element_destructor_fn destructor){
    destructor(v->data);
    free(v);
}

void treap_delete(treap_t** t){
    treap_delete_helper((*t),(*t)->root);
	free(*t);
	(*t) = NULL;
}

static void treap_delete_helper(treap_t* t,treap_node_t* v){
    if(v!=NULL){
        treap_delete_helper(t,v->left);
        treap_delete_helper(t,v->right);
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



void treap_insert(treap_t* t,void* data){
    t->root = treap_insert_helper(t,t->root,data);
}

static treap_node_t* treap_insert_helper(treap_t* t,treap_node_t* v,void* data){
    if(v==NULL){
        v = treap_new_node(data,t->constructor);
    }
    else if(t->comparator(data,v->data)<0){
        v->left = treap_insert_helper(t,v->left,data);
        if(v->left->priority > v->priority){
            v = treap_right_rotate(v);
        }
    }
    else{
        v->right = treap_insert_helper(t,v->right,data);
        if(v->right->priority > v->priority){
            v = treap_left_rotate(v);
        }
    }
    return v;

}

void treap_remove(treap_t* t,void* data){
    t->root = treap_remove_helper(t,t->root,data);
}

static treap_node_t* treap_remove_helper(treap_t* t,treap_node_t* v,void* data){
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
        if(v->left==NULL){
            treap_node_t* tmp = v->right;
            treap_delete_node(v,t->destructor);
            v = tmp;
        }
        else if(v->right==NULL){
            treap_node_t* tmp = v->left;
            treap_delete_node(v,t->destructor);
            v = tmp;
        }
        else{
            if(v->left->priority < v->right->priority){
                v = treap_left_rotate(v);
                v->left = treap_remove_helper(t,v->left,data);
            }
            else{
                v = treap_right_rotate(v);
                v->right = treap_remove_helper(t,v->right,data);
            }
        }
    }
    return v;
}

int treap_find(treap_t* t,void* data){
    return treap_find_helper(t,t->root,data);
}

static int treap_find_helper(treap_t* t,treap_node_t* v,void* data){
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
