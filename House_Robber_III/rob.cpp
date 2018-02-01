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
    int rob(TreeNode* root) {
        vector<int> result = robber(root);
        return max(result[0], result[1]);
    }
private:
    vector<int> robber(TreeNode* root) {
        if (root == NULL) return {0,0};
        vector<int> result(2);
        vector<int> left = robber(root->left);
        vector<int> right = robber(root->right);
        
        result[0] = max(left[0], left[1]) + max(right[0], right[1]);
        result[1] = left[0] + right[0] + root->val;
        return result;
    }
};
