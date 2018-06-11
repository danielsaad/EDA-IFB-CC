int is_equal_helper(tree_t* t,
    tree_node_t* node1,
    tree_node_t* node2){
    if(node1 == NULL && node2 == NULL){
        return 1;
    }
    if( (node1 == NULL && node2 != NULL) || 
        (node1 !=NULL && node2 == NULL)) {
        return 0;
    }
    if(t->comparator(node1->data,node2->data)!=0){
        return 0;
    }
    return is_equal_helper(t,node1->left,node2->left) &&
        is_equal_helper(t,node1->right,node2->right);
}

int is_equal(tree_t* t1, tree_t* t2){
    return(is_equal_helper(t1,t1->root,t2->root));
}