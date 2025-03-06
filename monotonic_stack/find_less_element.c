#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEW(ttype, size) (ttype*)malloc(size * sizeof(ttype))
#define FREE(x) if (x != NULL) free(x)

void print_list(int* nums, int size) {
  for (int i = 0; i < size; i++) {
    if (nums[i] < 0) {
      printf("-1, ");
    } else {
      printf("%d, ", nums[i]);
    }
  }
  printf("\n");
}

void find_prev_less(int* nums, int* prev_less, int size) {
  int* stack = (int*)malloc(size * sizeof(int));
  int top = -1;

  for (int i = 0; i < size; i++) {
    while (top >= 0 && nums[stack[top]] > nums[i]) {
      top--;
    }
    prev_less[i] = (top == -1) ? -1 : stack[top];
    stack[++top] = i;
  }
  free(stack);
}

void find_next_less(int* nums, int* next_less, int size) {
  int* stack = (int*)malloc(size * sizeof(int));

  int top = -1;

  for (int i = 0; i < size; i++) {
    while (top >= 0 && nums[stack[top]] > nums[i]) {
      int x = stack[top--];
      next_less[x] = i;
    }
    stack[++top] = i;
  }
  free(stack);
}

void find_prev_large(int* nums, int* prev_large, int size) {
  int* stack = (int*)malloc(size * sizeof(int));
  int top = -1;

  for (int i = 0; i < size; i++) {
    while (top >= 0 && nums[stack[top]] < nums[i]) {
      top--;
    }
    prev_large[i] = top == -1 ? -1 : stack[top];
    stack[++top] = i;
  }
  free(stack);
}

void find_next_large(int* nums, int* next_large, int size) {
  int* stack = (int*)malloc(size * sizeof(int));
  int top = -1;

  for (int i = 0; i < size; i++) {
    while (top >= 0 && nums[stack[top]] < nums[i]) {
      int x = stack[top--];
      next_large[x] = i;
    }
    stack[++top] = i;
  }
  free(stack);
}

int main(int argc, char** argv) {
  int nums[] = {73, 74, 75, 71, 69, 72, 76, 73};
  int size = sizeof(nums) / sizeof(nums[0]);

  int* prev_less = NEW(int, size);
  int* next_less = NEW(int, size);
  int* prev_large = NEW(int, size);
  int* next_large = NEW(int, size);

  find_prev_less(nums, prev_less, size);
  print_list(prev_less, size);

  find_next_less(nums, next_less, size);
  print_list(next_less, size);

  find_prev_large(nums, prev_large, size);
  print_list(prev_large, size);

  find_next_large(nums, next_large, size);
  print_list(next_large, size);

  FREE(prev_less);
  FREE(next_less);
  FREE(prev_large);
  FREE(next_large);

  return 0;
}
