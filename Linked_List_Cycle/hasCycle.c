#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* hasCycle(struct ListNode *head) {
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return slow;
    }
    return NULL;
}

struct ListNode* findCycleEntry(struct ListNode *head) {
    struct ListNode *meet = hasCycle(head);
    if (!meet) return NULL;
    
    struct ListNode *p1 = head;
    struct ListNode *p2 = meet;
    
    while (p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;
}

void breakCycle(struct ListNode *entry) {
    struct ListNode *cur = entry;
    while (cur->next != entry) {
        cur = cur->next;
    }
    cur->next = NULL;
}

void freeList(struct ListNode *head) {
    while (head) {
        struct ListNode *tmp = head;
        head = head->next;
        free(tmp);
    }
}
void freeListWithCycle(struct ListNode *head) {
    struct ListNode *entry = findCycleEntry(head);
    if (entry) {
        breakCycle(entry);
    }
    freeList(head);
}

int main(void) {
    struct ListNode *head = malloc(sizeof(struct ListNode));
    struct ListNode *n2   = malloc(sizeof(struct ListNode));
    struct ListNode *n3   = malloc(sizeof(struct ListNode));
    
    head->val = 1; head->next = n2;
    n2->val   = 2; n2->next   = n3;
    n3->val   =3;  n3->next   = head;
    
    printf("Has Cycling list? (%s)\n", (hasCycle(head) ? "YES" : "NO"));
    
    freeListWithCycle(head);
    return 0;
}
