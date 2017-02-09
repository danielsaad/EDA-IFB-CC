#include "../Utils/alloc.h"
#include "bst.h"

static bst_node_t* bst_insert_helper(bst_t * t,bst_node_t* v,void* data);

static void bst_delete_helper(bst_t* t,bst_node_t* v);

static int bst_find_helper(bst_t* t, bst_node_t* v,void *data);

static bst_node_t* bst_remove_helper(bst_t* t, bst_node_t* v,void* data);

static bst_node_t* bst_find_rightmost(bst_node_t* v);

static bst_node_t* bst_new_node(void* data,bst_element_constructor_fn constructor);

static void bst_delete_node(bst_node_t* node,bst_element_destructor_fn destructor);


static void bst_delete_node(bst_node_t* node,bst_element_destructor_fn destructor){
    destructor(node->data);
    free(node);
}


static bst_node_t* bst_new_node(void* data,bst_element_constructor_fn constructor){
    bst_node_t* ptr = mallocx(sizeof(bst_node_t));
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->data = constructor(data);
    return ptr;
}


void bst_initialize(bst_t** t,
                    bst_element_constructor_fn constructor,
                    bst_element_destructor_fn destructor,
                    bst_tree_element_compare_fn comparator){
    (*t) = mallocx(sizeof(bst_t));
    (*t)->root = NULL;
    (*t)->size = 0;
    (*t)->comparator = comparator;
    (*t)->constructor = constructor;
    (*t)->destructor = destructor;
}

void bst_delete(bst_t** t){
    bst_delete_helper((*t),(*t)->root);
    free(*t);
    (*t) = NULL;
}


static void bst_delete_helper(bst_t* t,bst_node_t* v){
    if(v!=NULL){
        bst_delete_helper(t,v->left);
        bst_delete_helper(t,v->right);
        bst_delete_node(v,t->destructor);
    }
}

static bst_node_t* bst_find_rightmost(bst_node_t* v){
    if(v==NULL || v->right==NULL){
        return v;
    }
    else{
        return bst_find_rightmost(v->right);
    }
}

void bst_insert(bst_t* t,void* data){
    t->root = bst_insert_helper(t,t->root,data);
}


static bst_node_t* bst_insert_helper(bst_t* t,bst_node_t* v,void* data){
    if(v==NULL){
        t->size++;
        v = bst_new_node(data,t->constructor);
    }
    else if(t->comparator(data,v->data)<0){
        v->left = bst_insert_helper(t,v->left,data);
    }
    else{
        v->right = bst_insert_helper(t,v->right,data);
    }
    return v;
}


void bst_remove(bst_t* t,void* data){
    t->root = bst_remove_helper(t,t->root,data);
}


static bst_node_t* bst_remove_helper(bst_t* t, bst_node_t* v,void* data){
    if(v==NULL){
        return v;
    }
    else if(t->comparator(data,v->data)<0){
        v->left = bst_remove_helper(t,v->left,data);
    }
    else if(t->comparator(data,v->data)>0){
        v->right =  bst_remove_helper(t,v->right,data);
    }
    else{ /*remoção do nó*/
        /*caso 1 e caso 2, o nó é uma folha ou só tem um filho. Solução: transplantar*/
        if(v->left==NULL){
            bst_node_t* tmp = v->right;
            bst_delete_node(v,t->destructor);
            t->size--;
            return tmp;
        }
        else if(v->right==NULL){
            bst_node_t* tmp = v->left;
            bst_delete_node(v,t->destructor);
            t->size--;
            return tmp;
        }
        /*caso 3, o nó tem dois filhos: achar o nó imediatamente acima do que queremos deletar
            obrigatoriamente este nó é uma folha.
            Solução: colocar o valor da folha no lugar que estamos e proceder a deletar a folha*/
        else{
            bst_node_t* tmp = bst_find_rightmost(v->left);
            void* swap = v->data;
            v->data = tmp->data;
            tmp->data = swap;
            v->left = bst_remove_helper(t,v->left,tmp->data);
        }
    }
    return v;
}



int bst_find(bst_t* t, void* data){
    return bst_find_helper(t,t->root,data);
}

static int bst_find_helper(bst_t* t, bst_node_t* v,void *data){
    if(v==NULL){
        return 0;
    }
    if(t->comparator(data,v->data)<0){
        return bst_find_helper(t,v->left,data);
    }
    else if(t->comparator(data,v->data)>0){
        return bst_find_helper(t,v->right,data);
    }
    return 1;
}



size_t bst_size(bst_t* t){
    return t->size;
}
