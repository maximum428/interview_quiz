#include <iostream>
/*
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int value) : val(value), next(NULL) {}
}; */

ListNode* addList(ListNode* head, int value) {
    ListNode* current = new ListNode(value);
    current->next = head;
    head = current;
    return head;
}
ListNode* insertNthNode(ListNode* head, int index, int value) {
    ListNode* current = head;
    ListNode* tmp = new ListNode(value);
    if (index < 0) return NULL;
    if (index == 0) {
        tmp->next = current;
        head = tmp;
    } else {
        while (current->next && --index) {
            current = current->next;
        }

        if (index > 1) {
            throw invalid_argument("Index is larger than link list size.");
        } else {
            tmp->next = current->next;
            current->next = tmp;
        }
    }
    return head;
}
ListNode* insertNodeInOrder(ListNode* head, int value) {
    ListNode* current = head;
    while (current->next) {
        if (current->next->val < value)
            current = current->next;
        else
            break;
    }
    ListNode* tmp = new ListNode(value);
    tmp->next = current->next;
    current->next = tmp;
    return current;
}
ListNode* appendList(ListNode* head, int value) {
    ListNode* current = head;
    
    while (current->next) {
        current = current->next;
    }
    current->next = new ListNode(value);
    //cout << current->val << endl;
    return current;
}

ListNode* removeFirstNode(ListNode* head) {
    ListNode *current = head, *tmp;
    if (head == nullptr) return NULL;
    tmp = current->next;
    current = tmp;
    return current;
}

ListNode* removeNthNode(ListNode* head, int index) {
    ListNode *current = head, *prev;
    if (index == 0) {
        prev = current->next;
        head = prev;
    } else {
        while (current && index--) {
            prev = current;
            current = current->next;
        }

        if (index < 0) {
            prev->next = current->next;
        } else {
            throw invalid_argument("Index is larger than link list size.");
        }
    }
    return head;
}

void removeHelper(ListNode* head, int value) {
    if (head == nullptr) return;
    else if (head->value = value) {
        head = head->next;
        removeHelper(head, value);
    } else {
        removeHelper(head->next, value);
    }
}
ListNode* deleteNodes(ListNode* head, int value) {
    removeHelper(head, value);
    return head;
}
ListNode* removeLastNode(ListNode* head) {
    ListNode *current = head, *prev;
    if (current == nullptr) return NULL;
    
    while (current->next) {
        prev = current;
        current = current->next;
    }
    prev->next = NULL;
    //current = prev;
    return head;
}
void printList(ListNode* head) {
    ListNode* current = head;
    while (current) {
        cout << current->val << ", ";
        current = current->next;
    }
    cout << "\n";
}
int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    //appendList(head, 3);
    //appendList(appendList(head, 4), 5);
    appendList(appendList(appendList(head, 4), 5), 6);
    //head = addList(head, 8);
    insertNodeInOrder(head, 3);
    head = insertNthNode(head, 1, 8);
    head = removeLastNode(head);
    head = removeNthNode(head, 7);
    printList(head);
}
