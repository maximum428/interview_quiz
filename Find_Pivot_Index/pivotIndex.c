int pivotIndex(int* nums, int numsSize) {
    int sum = 0, sub_sum = 0, i;
    
    for (i = 0; i < numsSize; i++) sum += nums[i];
    
    for (i = 0; i < numsSize; i++) {
        if (sub_sum == sum - nums[i] - sub_sum) return i;
        sub_sum += nums[i];
    }
    return -1;
}
