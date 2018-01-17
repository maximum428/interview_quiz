#include<stdio.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int findUnsortedSubarray(int *nums, int size) {
    int i, min = INT_MAX, max = INT_MIN;
    
    for (i = 0; i < size; i++) {
        if (nums[i] < min) {
            min = MIN(min, nums[i]);
        }
        if (nums[i] > max) {
            max = MAX(max, nums[i]);
        }
    }
    
    int l, r;
    for (l = 0; l < size; l++) {
        if (min < *(nums+l))
            break;
    }
    for (r = size-1; r >= 0; r--) {
        if (max > *(nums+r))
            break;
    }
    
    return r-l < 0 ? 0 : r-l+1;
}

int main(void) {
    int nums[7] = {2, 6, 4, 8, 10, 9, 15};
    
    printf("%d\n", findUnsortedSubarray(&nums, sizeof(nums)/sizeof(nums[0])));
    return 0;
}
