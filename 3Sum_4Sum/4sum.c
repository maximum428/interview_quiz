#include <stdio.h>
#include <stdlib.h>


int compare(const int* a, const int* b) {
  //return (*(int*)a - *(int*)b);
  return (*a - *b);
}
/*
int compare(const void* a, const void* b) {
  return (*(int*)a - *(int*)b);
}*/

void backtrack(int* nums, int size, int** res, int* res_size, int* vec, int vec_size, int target, int value, int start) {
  if (vec_size == 4 && value == target) {
    res[*res_size] = (int*)malloc(4 * sizeof(int));
    for (int i = 0; i < 4; i++) {
      res[*res_size][i] = vec[i];
    }
    (*res_size)++;
    return;
  }

  for (int i = start; i < size; i++) {
    if (i > start && nums[i] == nums[i-1]) continue;

    vec[vec_size] = nums[i];
    backtrack(nums, size, res, res_size, vec, vec_size+1, target, value+nums[i], i+1);
  }
}

int** four_sum2(int* nums, int size, int* res_size, int target) {
  int** res = (int**)malloc(1000 * sizeof(int*));
  int* vec = (int*)malloc(4 * sizeof(int));
  //qsort(nums, size, sizeof(int), compare);
  qsort(nums, size, sizeof(int), (int (*)(const void*, const void*))compare);
  backtrack(nums, size, res, res_size, vec, 0, target, 0, 0);
  free(vec);
  return res;
}


int** four_sum1(int* nums, int size, int* res_size, int target) {
  int** res = (int**)malloc(1000 * sizeof(int*));
  *res_size = 0;
  if (size < 4) {
    return res;
  }

  qsort(nums, size, sizeof(int), (int (*)(const void*, const void*))compare);

  for (int i = 0; i < size - 3; i++) {
    if (i > 0 && nums[i] == nums[i-1]) continue;
    for (int j = i+1; j < size - 2; j++) {
      if (j > i+1 && nums[j] == nums[j-1]) continue;
      int third = j + 1, four = size - 1;
      while (third < four) {
        int sum = nums[i] + nums[j] + nums[third] + nums[four];
        if (sum < target) {
          third++;
        } else if (sum > target) {
          four--;
        } else {
          res[*res_size] = (int*)malloc(4 * sizeof(int));
          res[*res_size][0] = nums[i];
          res[*res_size][1] = nums[j];
          res[*res_size][2] = nums[third];
          res[*res_size][3] = nums[four];
          (*res_size)++;

          while (third < four && nums[third] == nums[third+1]) third++;
          while (third < four && nums[four] == nums[four-1]) four--;
        }
      }
    }
  }
  return res;
}

void print_result(int** res, int res_size) {
  for (int i = 0; i < res_size; i++) {
    printf("[");
    for (int j = 0; j < 4; j++) {
      printf("%d ", res[i][j]);
    }
    printf("]\n");
  }
}

int main(int argc, char** argv) {
  int nums[] = {1, 0, -1, 0, -2, 2};
  int target = 0;
  int size = sizeof(nums)/sizeof(nums[0]);
  int res_size = 0;

  int** res1 = four_sum1(nums, size, &res_size, target);
  print_result(res1, res_size);
  
  res_size = 0;
  int** res2 = four_sum2(nums, size, &res_size, target);
  print_result(res2, res_size);

  return 0;
}
