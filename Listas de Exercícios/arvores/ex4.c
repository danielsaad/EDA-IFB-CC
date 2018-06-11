int number_of_leafs_helper(tree_node_t* node){
    if(node == NULL){
        return 0;
    }
    if(node->left == NULL && node->right == NULL){
        return 1;
    }
    return number_of_leafs_helper(node->left) + number_of_leafs_helper(node->right);
}


int number_of_leafs(tree_t* t){
    return number_of_leafs_helper(t->root);
}
