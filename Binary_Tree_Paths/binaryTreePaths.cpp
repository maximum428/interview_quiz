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
    vector<string> binaryTreePaths(TreeNode* root) {
        if (root == nullptr) return vec;
        Helper(root, "");
        return vec;
    }
    
    void Helper(TreeNode* root, string value) {
        if (!root->left && !root->right) {
            vec.push_back(value == "" ? to_string(root->val) : value + "->" + to_string(root->val));
        }
        if (root->left) Helper(root->left, value == "" ? to_string(root->val) : value + "->" + to_string(root->val));
        if (root->right) Helper(root->right, value == "" ? to_string(root->val) : value + "->" + to_string(root->val));
    }
        
private:
    vector<string> vec;
};
