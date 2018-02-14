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
    void removeHelper(ListNode *&head, int val) {
        if (head == nullptr) {
            return;
        }
        else if (head->val == val) {
            head = head->next;
            removeHelper(head, val);
        }
        else {
            removeHelper(head->next, val);
        }
    }
    
    ListNode* removeElements(ListNode* head, int val) {
        removeHelper(head, val);
        return head;
    }
};
