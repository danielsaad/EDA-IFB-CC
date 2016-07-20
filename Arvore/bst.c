#include "../Utils/alloc.h"
#include "bst.h"


static bst_node_t* bst_insert_helper(bst_node_t* v,void* data,
                              bst_element_compare_fn comparator,
                              bst_element_constructor_fn constructor);
static void bst_delete_helper(bst_node_t* v,bst_element_destructor_fn destructor);
static int bst_find_helper(bst_node_t* v,void *data,bst_element_compare_fn comparator);
static bst_node_t* bst_remove_helper(bst_node_t* v,void *data,bst_element_compare_fn comparator,bst_element_destructor_fn destructor);
static bst_node_t* bst_find_rightmost(bst_node_t* v);
bst_node_t* bst_new_node(void* data,bst_element_constructor_fn constructor);
void bst_delete_node(bst_node_t* node,bst_element_destructor_fn destructor);

void bst_delete_node(bst_node_t* node,bst_element_destructor_fn destructor){
    destructor(node->data);
    free(node);
}


static bst_node_t* bst_find_rightmost(bst_node_t* v){
    if(v==NULL || v->right==NULL){
        return v;
    }
    else{
        return bst_find_rightmost(v->right);
    }
}


static int bst_find_helper(bst_node_t* v,void *data,bst_element_compare_fn comparator){
    if(v==NULL){
        return 0;
    }
    if(comparator(data,v->data)<0){
        return bst_find_helper(v->left,data,comparator);
    }
    else if(comparator(data,v->data) >0){
        return bst_find_helper(v->right,data,comparator);
    }
    return 1;
}


static bst_node_t* bst_remove_helper(bst_node_t* v,void* data, bst_element_compare_fn comparator,
                          bst_element_destructor_fn destructor){
        if(v==NULL){
            return v;
        }
        else if(comparator(data,v->data)<0){
            v->left = bst_remove_helper(v->left,data,comparator,destructor);
        }
        else if(comparator(data,v->data)>0){
            v->right =  bst_remove_helper(v->right,data,comparator,destructor);
        }
        else{ /*remoção do nó*/
            /*caso 1 e caso 2, o nó é uma folha ou só tem um filho. Solução: transplantar*/
            if(v->left==NULL){
                bst_node_t* tmp = v->right;
                bst_delete_node(v,destructor);
                return tmp;
            }
            else if(v->right==NULL){
                bst_node_t* tmp = v->left;
                bst_delete_node(v,destructor);
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
                v->left = bst_remove_helper(v->left,tmp->data,comparator,destructor);
            }
        }
        return v;
    }

bst_node_t* bst_new_node(void* data,bst_element_constructor_fn constructor){
    bst_node_t* ptr = mallocx(sizeof(bst_node_t));
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->data = constructor(data);
    return ptr;
}


void bst_initialize(bst_t** t,
                    bst_element_constructor_fn constructor,
                    bst_element_destructor_fn destructor,
                    bst_element_compare_fn comparator){
    (*t) = mallocx(sizeof(bst_t));
    (*t)->root = NULL;
    (*t)->size = 0;
    (*t)->comparator = comparator;
    (*t)->constructor = constructor;
    (*t)->destructor = destructor;
}

void bst_delete(bst_t** t){
    bst_delete_helper((*t)->root,(*t)->destructor);
    free(*t);
    (*t) = NULL;
}

static void bst_delete_helper(bst_node_t* v,bst_element_destructor_fn destructor){
    if(v!=NULL){
        bst_delete_helper(v->left,destructor);
        bst_delete_helper(v->right,destructor);
        destructor(v->data);
        free(v);
    }
}

void bst_insert(bst_t* t,void* data){
    t->root = bst_insert_helper(t->root,data,t->comparator,t->constructor);
}

static bst_node_t* bst_insert_helper(bst_node_t* v,void* data,
                              bst_element_compare_fn comparator,
                              bst_element_constructor_fn constructor){
    if(v==NULL){
        v = bst_new_node(data,constructor);
    }
    else{
        if(comparator(data,v->data)<0){
            v->left = bst_insert_helper(v->left,data,comparator,constructor);
        }
        else{
            v->right = bst_insert_helper(v->right,data,comparator,constructor);
        }
    }
    return v;
}

void bst_remove(bst_t* t,void* data){
    t->root = bst_remove_helper(t->root,data,t->comparator,t->destructor);
}

int bst_find(bst_t* t, void* data){
    return bst_find_helper(t->root,data,t->comparator);
}
