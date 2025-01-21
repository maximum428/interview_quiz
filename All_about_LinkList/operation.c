#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
};

void push(struct Node **head, int data) {
  struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
  new_node->data = data;
  new_node->next = NULL;

  if (*head == NULL) {
    *head = new_node;
  } else {
    struct Node *curr = *head;
    while (curr->next != NULL) {
      curr = curr->next;
    }
    curr->next = new_node;
  }
}

void push_top(struct Node **head, int data) {
  struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
  new_node->data = data;
  new_node->next = *head;

  *head = new_node;
}

int insert_by_value(struct Node **head, int data) {
  struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
  new_node->data = data;
  new_node->next = NULL;

  if (*head == NULL) {
    return -1;
  } else if ((*head)->data > data) {
    new_node->next = *head;
    *head = new_node;
    return 0;
  }
  struct Node *curr = *head;
  while (curr->next != NULL) {
    if (curr->next->data > data) {
      new_node->next = curr->next;
      curr->next = new_node;
      return 0;
    }
    curr = curr->next;
  }
  if (curr->data <= data) {
    curr->next = new_node;
    return 0;
  }
  return -1;
}

int insert_by_index(struct Node **head, int index, int data) {
  struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
  new_node->data = data;
  new_node->next = NULL;

  if (index < 0) {
    return -1;
  } else if (index == 0) {
    new_node->next = *head;
    *head = new_node;
  } else if (*head != NULL) {
    struct Node *curr = *head;
    for (int i = 1; i < index; i++) {
      if (curr == NULL) {
        return -1;
      }
      curr = curr->next;
    }
    new_node->next = curr->next;
    curr->next = new_node;
  }
  return 0;
}

int pop(struct Node **head) {
  int res = -1;
  if (*head == NULL) {
    return res;
  } else if ((*head)->next == NULL) {
    res = (*head)->data;
    *head = NULL;
    free(*head);
    return res;
  }
  struct Node *tmp = NULL;
  tmp = (*head)->next;
  res = tmp->data;
  free(*head);
  *head = tmp;
  return res;
}

int pop_last(struct Node **head) {
  int ret = -1;
  if (*head == NULL) {
    return ret;
  } else if ((*head)->next == NULL) {
    ret = (*head)->data;
    *head = NULL;
    free(*head);
    return ret;
  }

  struct Node *curr = *head;
  while (curr->next->next != NULL) {
    curr = curr->next;
  }
  ret = curr->next->data;
  free(curr->next->next);
  curr->next = NULL;
  return ret;
}

int remove_by_value(struct Node **head, int data) {
  int ret = -1;
  if (*head == NULL) {
    return ret;
  } else if ((*head)->data == data) {
    struct Node *del_node = *head;
    *head = (*head)->next;
    free(del_node);
    return 0;
  }
  struct Node *curr = *head;
  while (curr->next != NULL) {
    if (curr->next->data == data) {
      struct Node *del_node = curr->next;
      curr->next = curr->next->next;
      free(del_node);
      return 0;
    }
    curr = curr->next;
  }
  return -1;
}

int remove_by_index(struct Node **head, int index) {
  int ret = -1;
  if (*head == NULL || index < 0) {
    return ret;
  } else if (*head != NULL && index == 0) {
    pop(head);
  }
  struct Node *curr = *head, *tmp;
  for(int i = 0; i < index - 1; i++) {
    if (curr->next == NULL) {
      return ret;
    }
    curr = curr->next;
  }
  tmp = curr->next;
  ret = curr->data;
  curr->next = tmp->next;
  free(tmp);
  return ret;
}

void traverse(struct Node *head) {
  if (head == NULL) {
    return;
  }
  struct Node *curr = head;
  while (curr != NULL) {
    printf("%d ", curr->data);
    curr = curr->next;
  }
  printf("\n");
}
int main(int argc, char** argv) {
  struct Node *head = NULL;
  push(&head, 20);
  push(&head, 30);
  push(&head, 40);

  push_top(&head, 10);
  insert_by_value(&head, 45);
  insert_by_index(&head, 2, 35);

  //pop_last(&head);
  //pop(&head);
  //pop_last(&head);
  //pop(&head);
  //pop(&head);
  //pop(&head);
  //remove_by_value(&head, 15);
  remove_by_index(&head, 3);
  
  traverse(head);
  return 0;
}
