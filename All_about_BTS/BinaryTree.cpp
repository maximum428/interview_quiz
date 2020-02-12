
void helper(TreeNode *root, int hd, map<int,int>& mp) {
    if (root == NULL) return;
    
    helper(root->left, hd-1, mp);
    mp[hd] += root->val;
    helper(root->right, hd+1, mp);
}

void VerticalSum(TreeNode *root) {
    map<int, int> mp;
    
    helper(root, 0, mp);
    map<int, int>::iterator iter;
    for (iter = mp.begin(); iter != mp.end(); iter++) {
        cout << iter->first << " : " << iter->second << endl;
    }
}

int MaximumWidth(TreeNode *root) {
    queue<TreeNode*> q;
    q.push(root);
    int res = 0;
    
    while (!q.empty()) {
        int size = q.size();
        res = max(res, size);
        auto node = q.front();
        q.pop();
        if (node->left != NULL)
            q.push(node->left);
        if (node->right != NULL)
            q.push(node->right);
    }
    return res;
}

int MaximumHeight(TreeNode *root) {
    if (root == NULL) return 0;
    
    int left = MaximumHeight(root->left);
    int right = MaximumHeight(root->right);
    if (left == 0 || right == 0)
        return left + right + 1;
    
    return max(left, right) + 1;
    //return 1 + max(MaximumHeight(root->left), MaximumHeight(root->right));
}

int MaximumHeight2(TreeNode *root) {
    queue<TreeNode*> q;
    q.push(root);
    int res = 0;
    
    while (!q.empty()) {
        int size = q.size();
        res++;
        for (int i = 0; i < size; i++) {
            auto node = q.front();
            q.pop();
            if (node->left != NULL)
                q.push(node->left);
            if (node->right != NULL)
                q.push(node->right);
        }
    }
    return res;
}

int MinimumWidth(TreeNode *root) {
    queue<TreeNode*> q;
    q.push(root);
    int res = INT_MAX;
    
    while (!q.empty()) {
        int size = q.size();
        res = min(res, size);
        auto node = q.front();
        q.pop();
        if (node->left != NULL)
            q.push(node->left);
        if (node->right != NULL)
            q.push(node->right);
    }
    return res;
}

int MinimumHeight(TreeNode *root) {
    if (root == NULL) return 0;
    
    int left = MinimumHeight(root->left);
    int right = MinimumHeight(root->right);
    if (left == 0 || right == 0)
        return left + right + 1;
    return min(left, right) + 1;
    /*if (root->left == NULL && root->right == NULL)
        return 1;
    if (root->left == NULL)
        return 1 + MinimumHeight(root->right);
    else if (root->right == NULL)
        return 1 + MinimumHeight(root->left);
    return 1 + min(MinimumHeight(root->left), MinimumHeight(root->right)); */
}

int MinimumHeight2(TreeNode *root) {
    queue<TreeNode *> q;
    q.push(root);
    int res = 0;
    while (!q.empty()) {
        res++;
        int size = q.size();
        for (int i = 0; i < size; i++) {
            auto node = q.front();
            q.pop();
            if (node->left == NULL && node->right == NULL) return res;
            if (node->left != NULL)
                q.push(node->left);
            if (node->right != NULL)
                q.push(node->right);
        }
    }
    return -1;
}

void PreOrderByRecursion(TreeNode* root) {
    if (root == NULL) return;
    
    cout << root->val << " ";
    PreOrderByRecursion(root->left);
    PreOrderByRecursion(root->right);
}

void InOrderByRecursion(TreeNode* root) {
    if (root == NULL) return;
    
    InOrderByRecursion(root->left);
    cout << root->val << " ";
    InOrderByRecursion(root->right);
}

void PostOrderByRecursion(TreeNode* root) {
    if (root == NULL) return;
    
    PostOrderByRecursion(root->left);
    PostOrderByRecursion(root->right);
    cout << root->val << " ";
}

void PreOrderByIteration(TreeNode* root) {
    if (root == NULL) return;
    
    stack<TreeNode*> stk;
    stk.push(root);
    
    while (!stk.empty()) {
        auto node = stk.top();
        stk.pop();
        cout << node->val << " ";
        if (node->right != NULL)
            stk.push(node->right);
        if (node->left != NULL)
            stk.push(node->left);
    }
}

void InOrderByIteration(TreeNode* root) {
    if (root == NULL) return;
    
    stack<TreeNode*> stk;
    TreeNode *current = root;
    while (current != NULL || !stk.empty()) {
        if (current != NULL) {
            stk.push(current);
            current = current->left;
        } else {
            current = stk.top();
            stk.pop();
            cout << current->val << " ";
            current = current->right;
        }
    }
}

void PostOrderByIteration(TreeNode* root) {
    if (root == NULL) return;
    stack<TreeNode*> stk, stk2;
    stk.push(root);
    
    while (!stk.empty()) {
        auto node = stk.top();
        stk.pop();
        stk2.push(node);
        if (node->left != NULL)
            stk.push(node->left);
        if (node->right != NULL)
            stk.push(node->right);
    }
    while (!stk2.empty()) {
        auto node = stk2.top();
        cout << node->val << " ";
        stk2.pop();
    }
}

void PostOrderByIteration2(TreeNode* root) {
    if (root == NULL) return;
    
    stack<TreeNode*> stk;
    stk.push(root);
    TreeNode *prev = NULL;
    
    while(!stk.empty()) {
        auto node = stk.top();
        if (!prev || prev->left == node || prev->right == node) {
            if (node->left != NULL)
                stk.push(node->left);
            else if (node->right != NULL)
                stk.push(node->right);
        } else if (node->left == prev) {
            if (node->right != NULL)
                stk.push(node->right);
        } else {
            cout << node->val << " ";
            stk.pop();
        }
        prev = node;
    }
}

TreeNode* helper3(vector<int>& preorder, vector<int>& inorder, int pre_start, int pre_end, 
                 int in_start, int in_end) {
    if (pre_start > pre_end || in_start > in_end) return NULL;
    
    TreeNode *root = new TreeNode(preorder[pre_start]);
    int midIndex = -1;
    for (int i = in_start; i <= in_end; i++) {
        if (inorder[i] == root->val)
            midIndex = i;
    }
    if (midIndex == -1) return NULL;
    int leftSize = midIndex - in_start;
    int rightSize = in_end - midIndex;
    root->left = helper3(preorder, inorder, pre_start+1, pre_start+leftSize, in_start, midIndex-1);
    root->right = helper3(preorder, inorder, pre_end-rightSize+1, pre_end, midIndex+1, in_end);
    return root;
}
TreeNode* constructFromPreIn(vector<int>& preorder, vector<int>& inorder) {
    return helper3(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
}

TreeNode* helper4(vector<int>& inorder, vector<int>& postorder, int in_start, int in_end, int post_start, int post_end) {
    if (in_start > in_end || post_start > post_end) return NULL;
    
    TreeNode *root = new TreeNode(postorder[post_end]);
    int midIndex = -1;
    for (int i = in_start; i <= in_end; i++) {
        if (inorder[i] == root->val)
            midIndex = i;
    }
    if (midIndex == -1) return NULL;
    int leftSize = midIndex - in_start;
    int rightSize = in_end - midIndex;
    root->left = helper4(inorder, postorder, in_start, midIndex-1, post_start, post_start+leftSize-1);
    root->right = helper4(inorder, postorder, midIndex+1, in_end, post_end-rightSize, post_end-1);
    return root;
}

TreeNode* constructFromInPost(vector<int>& inorder, vector<int>& postorder) {
    if (inorder.size() != postorder.size()) return NULL;
    return helper4(inorder, postorder, 0, inorder.size()-1, 0, postorder.size()-1);
}

TreeNode* helper5(vector<int>& preorder, vector<int>& postorder, int& preindex, int& postindex) {
    TreeNode *root = new TreeNode(preorder[preindex++]);
    if (root->val != postorder[postindex])
        root->left = helper5(preorder, postorder, preindex, postindex);
    if (root->val != postorder[postindex])
        root->right = helper5(preorder, postorder, preindex, postindex);
    postindex++;
    return root;
}

TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
    TreeNode *res;
    if (preorder.size() == 0 || preorder.size() != postorder.size()) return NULL;
    int preindex = 0, postindex = 0;
    res = helper5(preorder, postorder, preindex, postindex);
    return res;
}

void helper2(TreeNode* root, TreeNode* &prev, TreeNode* &head) {
    if (root == NULL) return;
    helper2(root->left, prev, head);
    if (head == NULL) {
        head = root;
        prev = root;
    } else {
        prev->right = root;
        root->left = prev;
        prev = root;
    }
    helper2(root->right, prev, head);
}

TreeNode* BinaryTree2DLL(TreeNode *root) {
    if (root == NULL) return NULL;
    
    TreeNode *head = NULL, *prev = NULL;
    helper2(root, prev, head);
    prev->right = head;
    head->left = prev;
    return head;
}

int main() {
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    
    VerticalSum(root);
    cout << "---------------------------\n";
    cout << "Maximum Width: " << MaximumWidth(root) << endl;
    cout << "---------------------------\n";
    cout << "Minimum Width: " << MinimumWidth(root) << endl;
    cout << "---------------------------\n";
    cout << "Maximum Depth: " << MaximumHeight2(root) << endl;
    cout << "---------------------------\n";
    cout << "Minimum Depth: " << MinimumHeight2(root) << endl;
    
    cout << "Preorder By Recursion:\n";
    PreOrderByRecursion(root);
    cout << "\nPreorder by Iteration:\n";
    PreOrderByIteration(root);
    cout << "\nInorder By Recursion:\n";
    InOrderByRecursion(root);
    cout << "\nInorder By Iteration:\n";
    InOrderByIteration(root);
    cout << "\nPostorder By Recursion:\n";
    PostOrderByRecursion(root);
    cout << "\nPostorder by Iteration(two stacks):\n";
    PostOrderByIteration(root);
    cout << "\nPostorder by Iteration(one stack):\n";
    PostOrderByIteration2(root);
    
    // Construct Binary Tree from Preorder and Inorder
    vector<int> preorder = {3, 9, 20, 15, 7}, inorder = {9, 3, 15, 20, 7};
    TreeNode *root2 = constructFromPreIn(preorder, inorder);
    // Construct Binary Tree from Inorder and Postorder
    vector<int> postorder = {9, 15, 7, 20, 3};
    TreeNode *root3 = constructFromInPost(inorder, postorder);
    // Construct Binary Tree from Preorder and Postorder
    preorder = {1, 2, 4, 5, 3, 6, 7}; postorder = {4, 5, 2, 6, 7, 3, 1};
    TreeNode *root4 = constructFromPrePost(preorder, postorder);
    
    BinaryTree2DLL(root2);
}
