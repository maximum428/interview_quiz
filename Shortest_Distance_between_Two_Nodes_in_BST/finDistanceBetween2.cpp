int distanceFromRoot(root, int a) {
    if (root == NULL) return 0;
    if (root->val < a)
        return 1 + distanceFromRoot(root->right, a);
    else
        return 1 + distanceFromRoot(root->left, a);
}

int distanceBetween2(TreeNode *root, int a, int b) {
    if (root == NULL) return 0;
    
    if (root->val > a && root->val > b)
        return distanceBetween2(root->left, a, b);
    if (root->val < a && root->val < b)
        return distanceBetween2(root->right, a, b);
    if (root->val >= a && root->val <= b)
        return distanceFromRoot(root, a) + distanceFromRoot(root, b);
}

int findDistanceBetween2(TreeNode *root, int a, int b) {
    if (a > b) swap(a, b);
    return distanceBetween2(root, a, b);
}
