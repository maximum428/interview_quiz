int addNumByList(ListNode *list1, ListNode *list2) {
    int sum = 0, carry = 0, pos = 1;
    int n = 0;
    
    while (list1 != NULL || list2 != NULL) {
        if (list1 != NULL)
            sum += list1->val;
        if (list2 != NULL)
            sum += list2->val;
        n += (sum % 10) * pos;
        sum /= 10;
        pos *= 10;
        if (list1 != NULL)
            list1 = list1->next;
        if (list2 != NULL)
            list2 = list2->next;
    }
    
    if (sum) {
        n += (sum % 10) * pos;
    }
    return n;
}

int main() {
    ListNode *list1, *list2;
    list1 = new ListNode(4);
    list1->next = new ListNode(5);
    list1->next->next = new ListNode(7);
    list2 = new ListNode(3);
    list2->next = new ListNode(6);
    cout << addNumByList(list1, list2) << endl;
}
