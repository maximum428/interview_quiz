#include <stdlib.h>
#include <stdio.h>


struct Node {
  int data;
  struct Node *next;
};

typedef struct Node2 {
  int data;
  struct Node2 *next;
} Node_t;

void append(struct Node **head, int data) {
  struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
  new_node->data = data;
  new_node->next = NULL;
  if (*head == NULL) {
    *head = new_node;
  } else {
    struct Node *tmp = *head;
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = new_node;
  }
}

void insert2(Node_t **head, int data) {
  Node_t *new_node = (Node_t*)malloc(sizeof(Node_t));
  new_node->data = data;
  new_node->next = NULL;
  if (*head == NULL) {
    *head = new_node;
  } else {
    Node_t *tmp = *head;
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = new_node;
  }
}
void traverse(struct Node *head) {
  if (head == NULL) {
    return;
  }
  struct Node *cur = head;
  while (cur != NULL) {
    printf("%d ", cur->data);
    cur = cur->next;
  }
  printf("\n");
}

void traverse2(Node_t *head) {
  if (head == NULL) {
    return;
  }
  Node_t *cur = head;
  while (cur != NULL) {
    printf("%d ", cur->data);
    cur = cur->next;
  }
  printf("\n");
}

void insertByValue(struct Node** head, int data) {
  struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
  new_node->data = data;
  new_node->next = NULL;

  if (*head == NULL) {
    return;
  }
  struct Node* cur = *head;
  if (cur->data > data) {
    new_node->next = cur;
    *head = new_node;
    return;
  }
  while (cur->next != NULL && cur->next->data < data) {
    cur = cur->next;
  }
  new_node->next = cur->next;
  cur->next = new_node;
}

void deleteByValue(struct Node** head, int data) {
  if (*head == NULL) {
    return;
  } else if ((*head)->data == data) {
    struct Node *del_node = (*head);
    (*head) = (*head)->next;
    free(del_node);
    return;
  }
  struct Node *cur = *head;
  while (cur->next != NULL && cur->next->data != data) {
    cur = cur->next;
  }
  if (cur->next != NULL && cur->next->data == data) {
    struct Node *del_node = cur->next, *next = cur->next->next;
    cur->next = next;
    free(del_node);
  }
}
void deleteByIndex(struct Node **head, int index) {
  struct Node* cur = *head;
  if (*head == NULL || index < 0) {
    return;
  }
  if (index == 0) {
    struct Node *del_node = *head, *cur = *head;
    *head = cur->next;
    free(del_node);
    return;
  }
  for (int i = 0; cur->next != NULL && i < index-1; i++) {
    cur = cur->next;
  }
  if (cur->next != NULL) {
    struct Node *del_node = cur->next;
    cur->next = cur->next->next;
    free(del_node);
  }
}

void insertByIndex(struct Node **head, int index, int data) {
  struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
  new_node->data = data;
  new_node->next = NULL;

  if (index == 0) {
    new_node->next = *head;
    *head = new_node;
    return;
  } else if (*head != NULL) {
    struct Node *cur = *head;
    for (int i = 1; cur != NULL && i < index; i++) {
      cur = cur->next;
    }
    new_node->next = cur->next;
    cur->next = new_node;
  }
}
int main() {
  struct Node *head = NULL;
  Node_t *head2 = NULL;

  append(&head, 10);
  append(&head, 20);
  append(&head, 30);

  insertByValue(&head, 35);

  deleteByValue(&head, 30);

  deleteByIndex(&head, 0);
  insertByIndex(&head, 0, 40);



  insert2(&head2, 40);
  insert2(&head2, 50);
  insert2(&head2, 60);

  traverse2(head2);

  traverse(head);

  return 0;
}


/*
1. traverse
2. append 
3. delete (remove) by position
4. Insert with index
5. Insert with value (less or large)
6. delete by value
*/
