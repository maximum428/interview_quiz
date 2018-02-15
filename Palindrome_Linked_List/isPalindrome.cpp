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
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return true;
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        // let slow reach pivot node  fast is alway double of slow
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            cout << "slow value: " << slow->val << "; fast value: " << fast->val << endl;
        }
        slow->next = reverseList(slow->next);
        cout << "slow next value: " << slow->next->val << endl;
        slow = slow->next;
        printList(slow);
        
        while (slow != nullptr) {
            cout << "head vlaue: " << head->val << "; slow value: " << slow->val << endl;
            if (head->val != slow->val) {
                cout << "return false" << endl;
                return false;
            }
            head = head->next;
            slow = slow->next;
        }
        cout << "return true\n" << endl;
        return true;
    }
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = NULL;
        ListNode* tmp = NULL;
        while (head != NULL) {
            tmp = head->next;
            head->next = prev;
            prev = head;
            head = tmp;
        }
        return prev;
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
    list1->next->next = new ListNode(3);
    list1->next->next->next = new ListNode(4);
    list1->next->next->next->next = new ListNode(4);
    list1->next->next->next->next->next = new ListNode(3);
    list1->next->next->next->next->next->next = new ListNode(2);
    list1->next->next->next->next->next->next->next = new ListNode(1);
    
    cout << (solution.isPalindrome(list1) == 0 ? "FALSE" : "TRUE") << endl;
