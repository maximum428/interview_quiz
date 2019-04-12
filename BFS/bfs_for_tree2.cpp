#include <iostream>
#include <queue>

/*
typedef struct Node {
    int val;
    Node *left, *right;
    Node(int value) : val(value), left(nullptr), right(nullptr) {}
} Node_t;
*/
class Node {
public:
    int val;
    Node *left, *right;
    Node(int value) : val(value), left(nullptr), right(nullptr) {}
};

void printLevelOrder(Node* root) {
    if (root == nullptr)
        return;
    
    queue<Node *> q;
    
    q.push(root);
    
    while (q.empty() == false) {
        Node *node = q.front();
        std::cout << node->val << " ";
        q.pop();
        
        if (node->left != nullptr)
            q.push(node->left);
        if(node->right != nullptr)
            q.push(node->right);
    }
}
int main() {
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    printLevelOrder(root);
    return 0;
}
