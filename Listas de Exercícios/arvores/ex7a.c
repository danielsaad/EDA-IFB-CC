
int is_zig_zag_helper(tree_node_t* node){
    if(node == NULL)
        return 1;
    if(node->left != NULL && node->right != NULL)
        return 0;
    if(node->left != NULL)
        return is_zig_zag_helper(node->left);
    return is_zig_zag_helper(node->right);
}

int is_zig_zag_recursive(tree_t* t){
    return is_zig_zag_helper(t->root);
}
