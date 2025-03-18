#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
  return (*(int*)a - *(int*)b);
}

int three_sum_smaller(int* nums, int size, int target) {
  if (size < 3) {
    return 0;
  }

  int count = 0;
  qsort(nums, size, sizeof(int), compare);

  for (int i = 0; i < size - 2; i++) {
    int second = i + 1, third = size - 1;
    while (second < third) {
      int sum = nums[i] + nums[second] + nums[third];
      if (sum < target) {
        count += (third - second++);
      } else {
        third--;
      }
    }
  }
  return count;
}

int main(int argc, char** argv) {
  int nums[] = {-2, 0, 1, 3};
  int target = 2;
  int size = sizeof(nums)/sizeof(nums[0]);
  printf("%d\n", three_sum_smaller(nums, size, target));

  return 0;
}
