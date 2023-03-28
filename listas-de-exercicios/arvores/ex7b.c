
int is_zig_zag(tree_t* t){
    tree_node_t* node =  t->root;
    while(node!=NULL){
        if(node->left != NULL && node->right != NULL){
            return 0;
        }
        if(node->left != NULL){
            node = node->left;
        }
        else{
            node = node->right;
        }
    }
    return 1;   
}
