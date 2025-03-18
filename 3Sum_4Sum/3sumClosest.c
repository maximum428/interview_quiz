#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compare(const void* a, const void* b) {
  return (*(int*)a - *(int*)b);
}

int three_sum_closest(int* nums, int size, int target) {
  if (size < 3) {
    return 0;
  }

  qsort(nums, size, sizeof(int), compare);
  int closest = nums[0] + nums[1] + nums[2];

  for (int i = 0; i < size - 2; i++) {
    int second = i + 1, third = size - 1;

    while (second < third) {
      int sum = nums[i] + nums[second] + nums[third];
      if (sum == target) {
        return sum;
      }
      if (abs(target - sum) < abs(target - closest)) {
        closest = sum;
      } else if (sum < target) {
        second++;
      } else {
        third--;
      }
    }
  }
  return closest;
}

int main(int argc, char** argv) {
  int nums[] = {-1, 2, 1, -4};
  int size = sizeof(nums)/sizeof(nums[0]);
  int target = 1;

  printf("%d\n", three_sum_closest(nums, size, target));

  return 0;
}
