#include <iostream>
/*
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
*/
bool isSymmetricHelper(TreeNode* left, TreeNode* right) {
    if (left == nullptr || right == nullptr)
        return left == right;
    if (left->val != right->val)
        return false;
    return isSymmetricHelper(left->left, right->right) && isSymmetricHelper(left->right, right->left);
}
bool isSymmetric1(TreeNode* root) {
    return root == nullptr || isSymmetricHelper(root->left, root->right);
}

bool isSymmetric2(TreeNode *root) {
    TreeNode *left, *right;
    if (!root)
        return true;
    queue<TreeNode*> q1, q2;
    q1.push(root->left);
    q2.push(root->right);
    while (!q1.empty() && !q2.empty()) {
        left = q1.front();
        q1.pop();
        right = q2.front();
        q2.pop();
        if (left == nullptr && right == nullptr)
            continue;
        if (left == nullptr || right == nullptr)
            return false;
        if (left->val != right->val)
            return false;
        q1.push(left->left);
        q1.push(left->right);
        q2.push(right->right);
        q2.push(right->left);
    }
    return true;
}

int main() {
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);
    cout << isSymmetric2(root) << endl;
}
