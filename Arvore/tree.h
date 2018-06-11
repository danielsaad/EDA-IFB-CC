#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
typedef void* (*tree_constructor_fn)(void* );
typedef void (*tree_destructor_fn)(void* );
typedef int (*tree_comparator_fn)(const void*, const void* );

typedef struct tree_node_t{
    struct tree_node_t* left;
    struct tree_node_t* right;
    void* data;
}tree_node_t;

typedef struct tree_t{
    tree_node_t* root;
    tree_constructor_fn constructor;
    tree_destructor_fn destructor;
    tree_comparator_fn comparator;
}tree_t;



void tree_initialize(tree_t** t, 
    tree_constructor_fn constructor,
    tree_destructor_fn destructor, 
    tree_comparator_fn comparator);

void tree_delete(tree_t** t);


#endif