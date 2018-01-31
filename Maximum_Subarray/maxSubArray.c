#include<stdio.h>

#define MAX(a, b) (((a)>(b))?(a):(b))
#define MIN(a, b) (((a)<(b))?(a):(b))

int maxSubArray1(int* nums, int numsSize) {
    int i, max;
    int f[numsSize];
    
    f[0] = nums[0];
    max = nums[0];
    for (i = 1; i < numsSize; i++) {
        f[i] = MAX(nums[i] + f[i - 1], nums[i]);
        max = MAX(max, f[i]);
    }
    
    return max;
}

int maxSubArray2(int* nums, int numsSize) {
    int i, max, sum;
    
    sum = nums[0];
    max = nums[0];
    for (i = 1; i < numsSize; i++) {
        sum = MAX(nums[i] + sum, nums[i]);
        max = MAX(max, sum);
    }
    
    return max;
}

int main(void) {
    int nums[9] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    printf("%d\n",maxSubArray1(nums, sizeof(nums)/sizeof(nums[0])));
    return 0;
}
