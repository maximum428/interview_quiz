bool findPath(TreeNode *root, vector<TreeNode*>& path, int k) {
    if (root == NULL) return false;
    
    path.push_back(root);
    
    if (root->val == k) return true;
    
    if ((root->left && findPath(root->left, path, k)) || 
        (root->right && findPath(root->right, path, k)))
        return true;
    
    path.pop_back();
    return false;
}

TreeNode *lca(TreeNode *root, int v1,int v2) {
		// Write your code here.
        vector<TreeNode*> path1, path2;

        if (!findPath(root, path1, v1) || !findPath(root, path2, v2))
            return NULL;

        int i;
        for (i = 0; i < path1.size() && i < path2.size(); i++) {
            if (path1[i] != path2[i])
                break;
        }
    
        for (auto i : path1)
            cout << i->val << ", ";
        cout << "\n";
        for (auto i : path2)
            cout << i->val << ", ";
        cout << "\n";
    
        return path1[i-1];
    }

int main() {
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    root->right->right->right = new TreeNode(6);
    
    TreeNode *result = lca(root, 4, 6);
    cout << result->val << endl;
    return 0;
}
