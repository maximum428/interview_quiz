/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int longestUnivaluePath(TreeNode* root) {
        int res = 0;
        travel(root, &res);
        return res;
    }
    
    int travel(TreeNode* root, int *res) {
        if (root == nullptr)
            return 0;
        int leftcount = travel(root->left, res);
        int rightcount = travel(root->right, res);
        int left = 0, right = 0;
        if (root->left && root->left->val == root->val)
            left = leftcount + 1;
        if (root->right && root->right->val == root->val)
            right = rightcount + 1;
        *res = max(*res, left+right);
        return max(left, right);
    }
};
