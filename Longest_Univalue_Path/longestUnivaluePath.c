/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#define MAX(a, b) (((a)>(b))?(a):(b))

int traverse(struct TreeNode* root, int *result) {
    if (root == NULL)
        return 0;
    
    int leftcount = traverse(root->left, result);
    int rightcount = traverse(root->right, result);
    int left = 0, right = 0;
    if (root->left && root->left->val == root->val)
        left = leftcount + 1;
    if (root->right && root->right->val == root->val)
        right = rightcount + 1;
    *result = MAX(*result, left+right);
    return MAX(left, right);
}

int longestUnivaluePath(struct TreeNode* root) {
    int result;
    traverse(root, &result);
    return result;
}
