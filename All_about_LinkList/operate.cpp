#include <iostream>

class Solution {
public:
    void deleteNode(ListNode* node) {
        auto next = node->next;
        *node = *next;
        delete next;
    }
    void deleteNode(ListNode* head_ref, int value) {
        ListNode* current = head_ref;
        while (current->next != NULL) {
            if (current->next->val == value) {
                current->next = current->next->next;
                return;
            }
            current = current->next;
        }
    }
    void deleteList(ListNode* head_ref) {
        ListNode* current = head_ref;
        ListNode* next;
        while (current != NULL) {
            next = current->next;
            delete current;
            current = next;
        }
        head_ref = NULL;
        cout << "Delete ListNode.\n";
    }
    void printList(ListNode* head_ref) {
        ListNode* current = head_ref;
        while (current != NULL) {
            cout << current->val << endl;
            current = current->next;
        }
        current = NULL;
    }
    void printNthNode(ListNode* head_ref, int index) {
        if (index < 1) return;
        ListNode* current = head_ref;
        while (--index) {
            if (current == NULL) {
                cout << "Index is out of range" << endl;
                return;
            }
            current = current->next;
        }
        cout << current->val << endl;
        current = NULL;
    }
    void appendNode(ListNode* head_ref, int value) {
        ListNode* current = head_ref;
        
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new ListNode(value);
        current = NULL;
    }
    void insertNode(ListNode* head_ref, int index, int value) {
        if (index < 1) return;
        ListNode* current = head_ref;
        index--;
        while (--index) {
            if (current == NULL) {
                cout << "Unable to reach " << index << "th node due to NULL vlaue" << endl;
                return;
            }
            current = current->next;
        }
        ListNode* next = current->next;
        current->next = new ListNode(value);
        current->next->next = next;
        next = NULL;
        current = NULL;
    }
    void addNode(ListNode* head_ref, int value) {
        ListNode* node = new ListNode(value);
        ListNode* current = head_ref;
        node->next = current;
        cout << "*** " << node->next->val << endl;
        current = node;
        cout << current->val << endl;
    }
};

int main() {
    ListNode* node = new ListNode(1);
    ListNode* next = new ListNode(2);
    node->next = next;
    next = new ListNode(3);
    node->next->next = next;
    next = new ListNode(4);
    node->next->next->next = next;
    //ListNode* head = node;
    
    Solution solution;
    /*
    while (node != NULL) {
        cout << "--" << node->val << endl;
        node = node->next;
    }
    node = head;
    */
    solution.printList(node);
    solution.printNthNode(node, 2);
    solution.appendNode(node, 5);
    cout << "---------------\n";
    solution.printList(node);
    solution.insertNode(node, 2, 6);
    cout << "---------------\n";
    solution.deleteNode(node, 3);
    solution.printList(node);
    //solution.addNode(node, 7);
    //cout << "==============\n";
    //solution.printList(node);
    cout << "node val: " << node->next->val << endl;
    
    //solution.deleteList(node);
    if (node != NULL) delete node;
}
