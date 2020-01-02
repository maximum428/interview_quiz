#include <iostream>

using namespace std;

struct Node {
    int val;
    Node *next;
    Node(int value) : val(value), next(nullptr) {}
};

void printListNode(Node *head) {
    if (head == nullptr)
        return;
    
    Node *current = head;
    while (current != nullptr) {
        cout << current->val << " ";
        current = current->next;
    }
    cout << "\n";
}

void push_back(Node **head, int value) {
    Node *current = *head;
    if (*head == nullptr) {
        *head = new Node(value);
        return;
    }
    
    while (current->next != nullptr)
        current = current->next;
    
    Node *new_node = new Node(value);
    current->next = new_node;
}

void push(Node **head, int value) {
    /*if (*head == nullptr) {
        *head = new Node(value);
        return;
    }*/
    
    Node *new_node = new Node(value);
    new_node->next = *head;
    *head = new_node;
}

void push_descending(Node **head, int value) {
    if (*head == nullptr) {
        *head = new Node(value);
        return;
    }
    
    Node *current = *head;
    while (current->next != nullptr && current->next->val > value) {
        current = current->next;
    }
    
    if (current->val <= value) { // add front
        Node *new_node = new Node(value);
        new_node->next = current;
        *head = new_node;
    } else {
        Node *tmp = current->next;
        current->next = new Node(value);
        current->next->next = tmp;
    }
    
    printListNode(*head);
}

void push_ascending(Node **head, int value) {
    if (*head == nullptr) {
        *head = new Node(value);
        return;
    }
    
    Node *current = *head;
    while (current->next != nullptr && current->next->val <= value) {
        current = current->next;
    }
    
    if (current->val > value) {  // add front
        Node *new_node = new Node(value);
        new_node->next = current;
        *head = new_node;
    } else { // add next
        Node *tmp = current->next;
        current->next = new Node(value);
        current->next->next = tmp;
    }
}

int pop(Node **head) {
    if (*head == nullptr)
        return -1;
    
    Node *current = (*head)->next;
    int retval = (*head)->val;
    *head = nullptr;
    *head = current;
    return retval;
}

int pop_back(Node *head) {
    if (head == nullptr)
        return -1;
    if (head->next == nullptr) {
        head = nullptr;
        return head->val;
    }
    
    Node *current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }
    int retval = current->next->val;
    current->next = nullptr;
    return retval;
}

void add_by_index(Node **head, int index, int value) {
    if (*head == nullptr || index < 0)
        return;

    Node *current = *head, *tmp = new Node(value);
    if (index == 0) {
        tmp->next = current;
        *head = tmp;
    } else {
        while (current->next && index--) {
            current = current->next;
        }
        
        if (index > 1) {
            throw invalid_argument("Index is larger than link list size.");
        } else {
            tmp->next = current->next;
            current->next = tmp;
        }
    }
}

int remove_by_index(Node **head, int index) {
    int retval = -1;
    Node *current = *head, *prev;
    
    if (*head == nullptr || index < 0)
        return -1;
    
    if (index == 0) {
        retval = (*head)->val;
        *head = (*head)->next;
    } else {
        while (current && index--) {
            prev = current;
            current = current->next;
        }
        cout << "Index: " << index << endl;
        if (index < 0) {
            retval = current->val;
            prev->next = current->next;
            //*head = prev;
        } else {
            throw invalid_argument("Index is larger than link list size.");
        }
        
    }
    return retval;
}

int remove_by_value(Node **head, int value) {
    Node *current = *head, *prev;
    int retval = -1;
    
    if (*head == nullptr)
        return retval;
    else if ((*head)->val == value) {
        retval = (*head)->val;
        *head = (*head)->next;
    } else {
        while (current != nullptr && current->val != value) {
            prev = current;
            current = current->next;
        }
    
        if (current == nullptr)
            return retval;
        else {
            retval = current->val;
            prev->next = current->next;
        }
    }
    return retval;
}

void removeHelper(Node **head, int value) {
    if (*head == nullptr) return;
    else if ((*head)->val == value) {
        *head = (*head)->next;
        removeHelper(&(*head), value);
    } else {
        removeHelper(&(*head)->next, value);
    }
}

void remove_by_all_value(Node **head, int value) {
    removeHelper(&(*head), value);
}

void reverse(Node **head) {
    Node *current = *head, *tmp, *prev = nullptr;
    
    while (current) {
        tmp = current->next;
        current->next = prev;
        prev = current;
        current = tmp;
    }
    *head = prev;
}

Node* reverseBetween(Node* head, int m, int n){
    if (head == NULL || m > n) return head;
    
    Node *dummy = new ListNode(0), *prev = dummy, *tmp;
    prev->next = head;
    
    for (int i = 0; i < m - 1; i++)
        prev = prev->next;
    
    head = prev->next;
    for (int i = 1; i <= n-m; i++) {
        tmp = prev->next;
        prev->next = head->next;
        head->next = head->next->next;
        prev->next->next = tmp;
    }
    return dummy->next;
}

Node *getLastNode(Node *head) {
    if (head == nullptr)
        return nullptr;
    
    Node *current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    
    return current;
}

void reverseTraversal(Node *head, Node *tail) {
    Node *current, *prev;
    if (tail != nullptr) {
        current = tail;
        while (current != head) {
            prev = head;
            while (prev->next != current) {
                prev = prev->next;
            }
            cout << current->val << " ";
            current = prev;
        }
        cout << current->val << endl;
    }
}

int main() {
    vector<int> vec = { 9, 3, 2, 5, 1, 8 };
    Node *head = nullptr;
    
    for (int i = 0; i < vec.size(); i++)
        //push(&head, vec[i]);
        //push_back(&head, vec[i]);
        push_ascending(&head, vec[i]);
        //push_descending(&head, vec[i]);
        
    
    printListNode(head);
    reverse(&head);
    printListNode(head);
    add_by_index(&head, 4, 8);
    printListNode(head);
    //remove_by_index(&head, 2);
    //printListNode(head);
    remove_by_all_value(&head, 8);
    printListNode(head);
    
    Node *tail = getLastNode(head);
    cout << "Last Node: " << tail->val << endl;
    reverseTraversal(head, tail);
    /*
    pop_back(head);
    printListNode(head);
    pop_back(head);
    printListNode(head);
    pop(&head);
    printListNode(head);
    */
    
}
