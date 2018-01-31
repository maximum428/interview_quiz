#include<stdio.h>

#define MAX(a, b) (((a)>(b))?(a):(b))
#define MIN(a, b) (((a)<(b))?(a):(b))

int maxSubArray(int* nums, int numsSize) {
    int i, max;
    int f[numsSize];
    
    f[0] = nums[0];
    for (i = 1; i < numsSize; i++) {
        f[i] = MAX(nums[i] + f[i - 1], nums[i]);
    }
    
    max = f[0];
    for (i = 1; i < numsSize; i++) {
        max = MAX(max, f[i]);
    }
    return max;
}

int main(void) {
    int nums[9] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    printf("%d\n",maxSubArray(nums, sizeof(nums)/sizeof(nums[0])));
    return 0;
}
