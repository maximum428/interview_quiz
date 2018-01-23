int dominantIndex(int* nums, int numsSize) {
    int maxOne = 0, maxTwo = 0, index = 0, i;
    
    for (i = 0; i < numsSize; i++) {
        if (maxOne < nums[i]) {
            maxTwo = maxOne;
            maxOne = nums[i];
            index = i;
        } else if (maxTwo < nums[i]) {
            maxTwo = nums[i];
        }
    }
    return maxOne >= maxTwo * 2 ? index : -1;
}
