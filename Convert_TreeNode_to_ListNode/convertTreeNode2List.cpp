void helper(TreeNode* root, TreeNode* &head, TreeNode* &prev) {
    if (root == NULL) return;
    
    helper(root->left, head, prev);
    
    if (prev == NULL)
      head = root;
    else {
       prev->right = root;
       root->left = prev;
    }
    prev = root;
    helper(root->right, head, prev);
}

TreeNode* convertTreeNode2List(TreeNode *root) {
    TreeNode *head = NULL, *prev = NULL;
    helper(root, head);
    return head;
}
