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
    int getMinimumDifference(TreeNode* root) {
        _prev = nullptr;
        min_diff = INT_MAX;
        inorder(root);
        return min_diff;
    }
    
    void inorder(TreeNode* root) {
        if (!root) return;
        inorder(root->left);
        if (_prev) min_diff = min(min_diff, abs(root->val - *_prev));
        _prev = &root->val;
        inorder(root->right);
    }
private:
    int* _prev;
    int min_diff;
};
