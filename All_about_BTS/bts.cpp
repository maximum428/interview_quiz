#include <iostream>
#include <queue>

using namespace std;

struct Tree_Node {
    int val;
    Tree_Node *left, *right;
    Tree_Node(int value) : val(value), left(nullptr), right(nullptr) {}
};

void printTreeNode(Tree_Node *root) {
    if (root == nullptr)
        return;
    
    queue<Tree_Node *> q;
    q.push(root);
    
    while (q.empty() == false) {
        Tree_Node *node = q.front();
        cout << node->val << " ";
        q.pop();
        
        if (node->left != nullptr)
            q.push(node->left);
        if (node->right != nullptr)
            q.push(node->right);
    }
    cout << "\n";
}

bool contain(Tree_Node *root, int value) {
    if (root == nullptr)
        return false;
    
    if (root->val == value)
        return true;
    else if (value < root->val)
        return contain(root->left, value);
    else
        return contain(root->right, value);
}

void insert(Tree_Node* &root, int value) {
    if (root == nullptr) {
        root = new Tree_Node(value);
        return;
    }
    
    if (value < root->val)
        insert(root->left, value);
    else
        insert(root->right, value);
}

Tree_Node* insert2(Tree_Node* root, int value) {
    if (root == nullptr)
        return new Tree_Node(value);
    
    if (value < root->val)
        root->left = insert2(root->left, value);
    else
        root->right = insert2(root->right, value);
    return root;
}

void insertIterative(Tree_Node **root, int value) {
    if (*root == nullptr) {
        *root = new Tree_Node(value);
        return;
    }
    
    Tree_Node *current = *root, *parent = nullptr;
    while (current != nullptr) {
        parent = current;
        
        if (value < current->val)
            current = current->left;
        else
            current = current->right;
    }
    
    if (value < parent->val)
        parent->left = new Tree_Node(value);
    else
        parent->right = new Tree_Node(value);
}

Tree_Node *findParent(Tree_Node *root, int value) {
    if (root == nullptr || root->val == value)
        return nullptr;
    
    if (value < root->val) {
        if (root->left == nullptr)
            return nullptr;
        else if (root->left->val == value)
            return root;
        else
            return findParent(root->left, value);
    } else {
        if (root->right == nullptr)
            return nullptr;
        else if (root->right->val == value)
            return root;
        else
            return findParent(root->right, value);
    }
}

Tree_Node *findNode(Tree_Node *root, int value) {
    if (root == nullptr)
        return nullptr;
    
    if (root->val == value)
        return root;
    else if (value < root->val)
        return findNode(root->left, value);
    else
        return findNode(root->right, value);
}

Tree_Node* remove(Tree_Node *root, int value) {
    if (root == nullptr)
        return nullptr;

    if (value < root->val) {
        root->left = remove(root->left, value);
        return root;
    } else if (value > root->val) {
        root->right = remove(root->right, value);
        return root;
    }
    
    if (root->left == nullptr) {
        Tree_Node *tmp = root->right;
        delete root;
        return tmp;
    } else if (root->right == nullptr) {
        Tree_Node *tmp = root->left;
        delete root;
        return tmp;
    } else {
        Tree_Node *succParent = root->right, *succ = root->right;
        while (succ->left != nullptr) {
            succParent = succ;
            succ = succ->left;
        }
        succParent->left = succ->right;
        
        root->val = succ->val;
        delete succ;
        return root;
    }
}

int findMin(Tree_Node *root) {
    if (root == nullptr)
        return -1;
    
    if (root->left == nullptr)
        return root->val;
    else
        return findMin(root->left);
}

int findMax(Tree_Node *root) {
    if (root == nullptr)
        return -1;
    
    if (root->right == nullptr)
        return root->val;
    else
        return findMax(root->right);
}

void preorder(Tree_Node *root) {
    if (root != nullptr) {
        cout << root->val << " ";
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(Tree_Node* root) {
    if (root != nullptr) {
        postorder(root->left);
        postorder(root->right);
        cout << root->val << " ";
    }
}

void inorder(Tree_Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }
}

int main() {
    vector<int> vec = { 3, 9, 2, 5, 1, 8};
    Tree_Node *root = nullptr;
    for (int v : vec) {
        //insert(root, v);
        //root = insert2(root, v);
        insertIterative(&root, v);
    }
    
    printTreeNode(root);
    cout << contain(root, 8) << endl;
    Tree_Node *parent = findParent(root, 8);
    if (parent == nullptr)
        cout << "Parent node not found." << endl;
    else
        cout << "Parent: " << parent->val << endl;

    Tree_Node *node = findNode(root, 2);
    if (node == nullptr)
        cout << "Node not found"<< endl;
    else
        cout << node->val << endl;
    //root = remove(root, 9);
    printTreeNode(root);
    cout << "smallest number : " << findMin(root) << endl;
    cout << "largetst number : " << findMax(root) << endl;
    preorder(root);
    cout << "\n";
    postorder(root);
    cout << "\n";
    inorder(root);
    cout << "\n";
}
