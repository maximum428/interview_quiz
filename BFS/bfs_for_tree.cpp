#include <iostream>
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

int getHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    } else {
        int lheight = getHeight(node->left);
        int rheight = getHeight(node->right);
        
        if (lheight > rheight) {
            return (lheight + 1);
        } else {
            return (rheight + 1);
        }
    }
}

void printGivenLevel(Node* root, int level) {
    if (root == nullptr)
        return;
    if (level == 1)
        std::cout << root->val << " ";
    else if (level > 1) {
        printGivenLevel(root->left, level-1);
        printGivenLevel(root->right, level-1);
    }
}
void printLevelOrder(Node* root) {
    int h = getHeight(root);
    int i;
    for (i = 1; i <= h; i++) {
        printGivenLevel(root, i);
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
