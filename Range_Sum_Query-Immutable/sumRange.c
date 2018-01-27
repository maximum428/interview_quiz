#include<stdio.h>

int *_sum;

typedef struct {
    int *nums;
    int numsSize;
} NumArray;

NumArray* numArrayCreate(int* nums, int numsSize) {
    int i;
    NumArray* num_array = NULL;
    if ((num_array = (NumArray*)malloc(sizeof(NumArray))) == NULL)
        return NULL;
    if ((num_array->nums = (int*)malloc(sizeof(int) * numsSize)) == NULL)
        return NULL;
    
    memcpy(num_array->nums, nums, sizeof(int) * numsSize);
    num_array->numsSize = numsSize;
    
    _sum = (int*)malloc(sizeof(int) * (numsSize+1));
    _sum[0] = 0;
    for (i = 0; i < numsSize; i++) {
        _sum[i + 1] = _sum[i] + nums[i];
    }
    
    return num_array;
}

int numArraySumRange1(NumArray* obj, int i, int j) {
    int sum = 0, k;
    for (k = i; k <= j; k++) {
        sum += obj->nums[k];
    }
    return sum;
}

int numArraySumRange2(NumArray* obj, int i, int j) {
    return _sum[j + 1] - _sum[i];
}

void numArrayFree(NumArray* obj) {
    if (obj == NULL) return;
        
    free(obj->nums);
    free(obj);
}

int main(void) {
    int nums[6] = {-2, 0, 3, -5, 2, -1};
    struct NumArray* obj = numArrayCreate(nums, sizeof(nums)/sizeof(nums[0]));
    printf("%d\n", numArraySumRange2(obj, 0, 2));
    numArrayFree(obj);
    free(_sum);
    return 0;
}
