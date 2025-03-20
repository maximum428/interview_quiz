#include <stdio.h>
#include <stdlib.h>

struct ListNode {
  int val;
  struct ListNode *next;
};

int addNumbByList(struct ListNode* list1, struct ListNode* list2) {
  int res = 0, sum = 0, pos = 1;

  while (list1 || list2) {
    if (list1) {
      sum += list1->val;
      list1 = list1->next;
    }
    if (list2) {
      sum += list2->val;
      list2 = list2->next;
    }
    res += (sum % 10) * pos;
    sum /= 10;
    pos *= 10;
  }

  if (sum > 0) {
    res += (sum % 10) * pos;
  }
  return res;
}

struct ListNode* createLinkedList(int* values, int size) {
  struct ListNode *head = NULL;
  struct ListNode *current = NULL;

  for (int i = 0; i < size; i++) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = values[i];
    newNode->next = NULL;
    if (!head) {
      head = newNode;
    } else {
      current->next = newNode;
    }
    current = newNode;
  }

  return head;
}

int main(int argc, char** argv) {
  int values1[] = {4, 5, 7};
  int values2[] = {3, 6};

  struct ListNode *root1 = createLinkedList(values1, 3);
  struct ListNode* root2 = createLinkedList(values2, 2);

  printf("%d\n", addNumbByList(root1, root2));

  free(root1);
  free(root2);

  return 0;
}
