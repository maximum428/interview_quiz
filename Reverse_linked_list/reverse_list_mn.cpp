#include <iostream>

using namespace std;

struct ListNode {
   int val;
   ListNode *next;
   ListNode(int value) : val(value), next(nullptr) {}
};

void reverseBetween(ListNode* head, int m, int n) {
   ListNode *m_list, *n_list, *tmp = head;
   if (head == nullptr) return;

   for (int i = 0; i < m-2; i++) {
      tmp = tmp->next;
   }
   m_list = tmp;
   for (int i = 0; i < n-2; i++) {
      tmp = tmp->next;
   }
   n_list = tmp;
   tmp = m_list->next;

   m_list->next = n_list->next;
   n_list->next = tmp;
   tmp->next = m_list->next->next;
   m_list->next->next = n_list;
}

int main() {
   ListNode *head = new ListNode(1);
   head->next = new ListNode(2);
   head->next->next = new ListNode(3);
   head->next->next->next = new ListNode(4);
   head->next->next->next->next = new ListNode(5);

   reverseBetween(head, 2, 4);
   ListNode *cur = head;
   while (cur != nullptr) {
      cout << cur->val << " -> ";
      cur = cur->next;
   }
   cout << "\n";
   return 0;
}
