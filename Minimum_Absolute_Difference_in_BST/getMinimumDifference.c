/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#define MIN(a,b) (((a)<(b))?(a):(b))

int *prev; // = NULL;
int min_diff; // = INT_MAX;

void traverse(struct TreeNode* root) {
    if (root == NULL) return;
    
    traverse(root->left);
    if (prev) min_diff = MIN(min_diff, root->val - *prev);
    prev = &root->val;
    traverse(root->right);
}

int getMinimumDifference(struct TreeNode* root) {
    prev = NULL;
    min_diff = INT_MAX;
    traverse(root);
    return min_diff;
}
