#include <iostream>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists1(ListNode* l1, ListNode* l2) {
        ListNode mylist(INT_MIN);
        ListNode* tail = &mylist;

        while( l1 && l2) {
            cout << "l1 value: " << l1->val << "; l2 value: " << l2->val << endl;
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
                if (l1 != nullptr) cout << "spot1: l1 value=" << l1->val << endl;
                else cout << "l1 reachs null";
            } else {
                tail->next = l2;
                l2 = l2->next;
                if (l2 != nullptr) cout << "spot2: l2 vlaue=" << l2->val << endl;
                else cout << "l2 reachs null";
            }
            tail = tail->next;
        }
        if (l1 == nullptr) cout << "l1 is null\n";
        if (l2 == nullptr) cout << "l2 is null\n";
        if (tail->next == l1) cout << "tail next = l1";
        if (tail->next == l2) cout << "tail next = l2";
        
        tail->next = l1 ? l1 : l2;
        return mylist.next;
    }
    
    ListNode* mergeTwoLists2(ListNode* l1, ListNode* l2) {
        if (l1 == NULL) { cout << "l1 is null\n"; return l2; }
        if (l2 == NULL) { cout << "l2 is null\n"; return l1; }
        
        cout << "l1 value: " << l1->val << "; l2 value: " << l2->val << endl;
        
        if (l1->val < l2->val) {
            cout << "spot 1\n";
            l1->next = mergeTwoLists2(l1->next, l2);
            return l1;
        } else {
            cout << "spot 2\n";
            l2->next = mergeTwoLists2(l2->next, l1);
            return l2;
        }
    }
    
    void printList(ListNode* head_ref) {
        ListNode* current = head_ref;
        
        while (current != nullptr) {
            cout << current->val << endl;
            current = current->next;
        }
    }
};

int main() {
    Solution solution;
    ListNode* list1 = new ListNode(1);
    list1->next = new ListNode(2);
    list1->next->next = new ListNode(4);
    ListNode* list2 = new ListNode(1);
    list2->next = new ListNode(3);
    list2->next->next = new ListNode(4);
    
    ListNode* newlist = solution.mergeTwoLists2(list1, list2);
    //ListNode* newlist = solution.mergeTwoLists1(list1, list2);
    solution.printList(newlist);
}
