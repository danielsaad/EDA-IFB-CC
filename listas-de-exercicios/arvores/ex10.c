typedef void* (*constructor_fn)(void*);
typedef void (*destructor_fn)(void*);
typedef int (*comparator_fn)(const void* a,const void* b);


typedef struct tree_node_t{
    void* data;
    tree_node_t* left;
    tree_node_t* right;
}tree_node_t;


typedef struct tree_t{
    tree_node_t* root;
    constructor_fn constructor;
    destructor_fn destructor_fn;
    comparator_fn comparator;
    int size;
}tree_t;

int is_bst(tree_t* t){
    return is_bst_helper(t,t->root,NULL,NULL);
}

int is_bst_helper(tree_t* t,tree_node_t* v,void* l,void* r){
    if(v==NULL){
        return 1;
    }
    int a,b;
    if(l==NULL || t->comparator(v->data,l)>0{
        a =1;
    }
    if(r==NULL || t->comparator(v->data,r)<0){
        b = 1;
    }
    return (a && b && is_bst_helper(t,v->left,l,v->data) && is_bst_helper(t,v->right,v->data,r));
}

