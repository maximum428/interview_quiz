#include <iostream>

void printNode(ListNode* head) {
    ListNode* current = head;
    do {
        cout << head->val << ", ";
        head = head->next;
    } while (head != current);
    cout << "\n";
}

void insertNode(ListNode* head, ListNode* target) {
    target->next = head->next;
    head->next = target;
}

void insertSortedList(ListNode* head, int k) {
    //ListNode* current = head;
    ListNode* target = new ListNode(k);
    
    while(head) {
        if (head->val < k && head->next->val > k) {
            insertNode(head, target);
            break;
        } else {
            if (head->val > head->next->val) {
                insertNode(head, target);
                break;
            }
        }
        head = head->next;
    }
}

int main() {
    ListNode* head = new ListNode(7);
    head->next = new ListNode(10);
    head->next->next = new ListNode(12);
    head->next->next->next = new ListNode(5);
    head->next->next->next->next = new ListNode(6);
    head->next->next->next->next->next = head;
    
    insertSortedList(head, 8);
    printNode(head);
    
    insertSortedList(head, 13);
    printNode(head);
    
    insertSortedList(head, 2);
    printNode(head);
    
}
