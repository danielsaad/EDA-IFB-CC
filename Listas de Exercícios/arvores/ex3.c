#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tree.h"

void pre_order_helper(tree_node_t* node){
    if(node != NULL){
        printf("%d ",*(int*)node->data);
        pre_order_helper(node->left);
        pre_order_helper(node->right);
    }
}   

void pre_order(tree_t* t){
    pre_order_helper(t->root);
}

void* int_constructor(void* data){
    void* ptr = malloc(sizeof(int));
    memcpy(ptr,data,sizeof(int));
    return ptr;
}

void int_destructor(void* data){
    free(data);
}

int int_comparator(const void* a, const void* b){
    int c,d;
    c = *(int*) a;
    d = *(int*) b;
    if(c<d)
        return -1;
    else if (c==d)
        return 0;
    else
        return 1;
}


tree_node_t* new_tree_node(tree_t* t,void* data){
    tree_node_t* ptr = malloc(sizeof(tree_node_t));
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->data = t->constructor(data);
    return ptr;
}

tree_node_t* build_tree_helper(tree_t* t,
    tree_node_t* node,
    char* seq_par,
    int* seq_value,
    int* i_par,int* i_value){
    node = NULL;
    if(seq_par[*i_par]=='('){
        node = new_tree_node(t,&seq_value[*i_value]);
        (*i_par)++;
        (*i_value)++;
        if(seq_par[*i_par] == '('){
            node->left = build_tree_helper(t,node->left,seq_par,seq_value,i_par,i_value);
        }
        if(seq_par[*i_par] == '('){
            node->right = build_tree_helper(t,node->right,seq_par,seq_value,i_par,i_value);
        }
        if(seq_par[*i_par] == ')'){
            (*i_par)++;
            return node;
        }
    }
    return node;
}
void build_tree(tree_t* t,char* seq_par,int* seq_value){
    int i_par = 0;
    int i_value = 0;
    t->root = build_tree_helper(t,t->root,seq_par,seq_value,&i_par,&i_value);
}






int main(){
    char seq_par[] = "(((()()))(()))";
    int seq_value[] = {1,3,2,5,4,8,9};
    tree_t* t;
    tree_t* t2;
    tree_initialize(&t,int_constructor,int_destructor,int_comparator);
    tree_initialize(&t2,int_constructor,int_destructor,int_comparator);
    build_tree(t,seq_par,seq_value);
    build_tree(t2,seq_par,seq_value);
    pre_order(t);
    printf("\nA arvore possui %d folhas.\n",number_of_leafs(t));
    if(is_zig_zag_recursive(t)){
        printf("A árvore é zig-zag");
    }
    else{
        printf("A árvore não é zig-zag.\n");
    }
    if(is_equal(t,t2)){
        printf("As árvores são iguais.\n");
    }
    else{
        printf("As árvores não são iguais.\n");
    }
    return 0;
}