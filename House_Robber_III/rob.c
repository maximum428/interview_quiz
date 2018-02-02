/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#define MAX(a, b) (((a)>(b))?(a):(b))

int* robber(struct TreeNode* root);

int rob(struct TreeNode* root) {
    int* result = robber(root);
    return MAX(result[0], result[1]);
}

int* robber(struct TreeNode* root) {
    if (root == NULL) {
        int* ret = (int*)malloc(sizeof(int) * 2);
        ret[0] = 0;
        ret[1] = 0;
        return ret;
    }
    
    int* result = (int*)malloc(sizeof(int) * 2);
    result[0] = 0;
    result[1] = 0;
    int* left = robber(root->left);
    int* right = robber(root->right);
    result[0] = MAX(left[0], left[1]) + MAX(right[0], right[1]);
    result[1] = left[0] + right[0] + root->val;
    return result;
}
