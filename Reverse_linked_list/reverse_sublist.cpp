#include <iostream>

using namespace std;

struct ListNode {
   int val;
   ListNode *next;
   ListNode(int value) : val(value), next(nullptr) {}
};

ListNode* reverse(ListNode *head) {
    ListNode *prev = nullptr, *curr = head, *tmp;
    while (curr) {
        tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }
    return prev;
}
ListNode* reverseBetween(ListNode* head, int m, int n) {
   if (m == n) return head;    

   ListNode *curr = head, *rvse_head, *rvse_prev, *rvse_tail, *rvse_next;
   int i = 1;
   while (curr && i <= n) {
       if (i < m) {
           rvse_prev = curr;
       } else if (i == m) {
           rvse_head = curr;
       } else if (i == n) {
           rvse_tail = curr;
           rvse_next = curr->next;
           break;
       }
       i++;
       curr = curr->next;
   }
   
   rvse_tail->next = nullptr;
   rvse_tail = reverse(rvse_head);
   if (rvse_prev) {
      rvse_prev->next = rvse_tail;
   } else {
       head = rvse_tail;
   }
   rvse_head->next = rvse_next;
   return head;
}

int main() {
   ListNode *head = new ListNode(10);
   head->next = new ListNode(20);
   head->next->next = new ListNode(30);
   head->next->next->next = new ListNode(40);
   head->next->next->next->next = new ListNode(50);
   head->next->next->next->next->next = new ListNode(60);
   head->next->next->next->next->next->next = new ListNode(70);

   reverseBetween(head, 3, 6);
   ListNode *cur = head;
   while (cur != nullptr) {
      cout << cur->val << " -> ";
      cur = cur->next;
   }
   cout << "\n";
   return 0;
}
