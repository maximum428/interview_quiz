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
    bool hasCycle(ListNode *head) {
        if (head == NULL) return false;
        ListNode *node = head;
        ListNode *searcher = head;
        while (searcher->next != NULL && searcher->next->next != NULL) {
            node = node->next;
            searcher = searcher->next->next;
            if (node == searcher) return true;
        }
        return false;
    }
};
