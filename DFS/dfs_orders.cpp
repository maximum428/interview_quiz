#include <iostream>

using namespace std;

typedef struct Node {
    int val;
    Node *left, *right;
    Node(int value) : val(value), left(nullptr), right(nullptr) {}
} Node_t;

void printInorder(Node *root) {
    if (root == nullptr)
        return;
    
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

void printPreorder(Node *root) {
    if (root == nullptr)
        return;
    
    cout << root->val << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

void printPostorder(Node *root) {
    if (root == nullptr)
        return;
    
    printPostorder(root->left);
    printPostorder(root->right);
    cout << root->val << " ";
}

int main() {
    Node_t *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    
    cout << "Inorder: ";
    printInorder(root);
    cout << endl << "Preorder: ";
    printPreorder(root);
    cout << endl << "Postorder: ";
    printPostorder(root);
}
