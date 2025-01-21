#include<stdio.h>

typedef struct List_Node {
    int val;
    struct List_Node* next;
    //void (*initialize)(struct List_Node *self, int value);
} List_Node_t;

void push(List_Node_t *head, int value){
    List_Node_t *current = head;
    
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = malloc(sizeof(List_Node_t));
    current->next->val = value;
    current->next->next = NULL;
}

int pop(List_Node_t **head) {
    int retval = -1;
    List_Node_t *next_node = NULL;
        
    if (*head == NULL) {
        return retval;
    } else if ((*head)->next == NULL) {
      retval = (*head)->data;
      *head = NULL;
      free(*head);
      return res;
    }
    
    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;
    
    return retval;
}

int pop_last(List_Node_t *head){
    int retval = -1;
    
    if (head == NULL)
        return retval;
    else if (head->next == NULL){
        retval = head->val;
        free(head);
        return retval;
    }
    
    List_Node_t *current = head;
    while (current->next->next != NULL){
        current = current->next;
    }
    retval = current->next->val;
    free(current->next);
    current->next = NULL;
    return retval;
}

void push_first(List_Node_t **head, int value){
    List_Node_t* new_node;
    new_node = malloc(sizeof(List_Node_t));
    new_node->val = value;
    new_node->next = *head;
    *head = new_node;
}
void print_list(List_Node_t *head){
    List_Node_t *current = head;
    
    while (current != NULL){
        printf("%d\n", current->val);
        current = current->next;
    }
}

int remove_by_index(List_Node_t **head, int index) {
    int retval = -1;
    if ((*head == NULL) || (index < 0)) {
        return -1;
    } else if (index == 0) {
        return pop(head);
    }
    
    List_Node_t *current = *head, *tmp = NULL;
    for (int i = 0; i < index - 1; i++) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }
    tmp = current->next;
    retval = current->val;
    current->next = tmp->next;
    free(tmp);
    
    return retval;
}

int remove_by_value(List_Node_t **head, int value) {
    if (*head == NULL) {
        return -1;
    }
    
    List_Node_t *current = *head;
    while (current->next != NULL) {
        if (current->next->val == value) {
            current->next = current->next->next;
        }
        current = current->next;
    }
    return 0;
}

int main() {
    List_Node_t *head = NULL;
    head = malloc(sizeof(List_Node_t));
    if (head == NULL){
        return 1;
    }
    
    head->val = 1;
    head->next = NULL;
    
    push(head, 2);
    push_first(&head, 3);
    push(head, 4);
    push(head, 5);
    remove_by_index(&head, 4);
    remove_by_value(&head, 2);
    

    print_list(head);
    return 0;
}
