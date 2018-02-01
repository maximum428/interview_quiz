#define MAX(a, b) (((a)>(b))?(a):(b))

int rob(int* nums, int numsSize) {
    int i, rob = 0;
    int no_rob = 0;
    for (i = 0; i < numsSize; i++) {
        int tmp = no_rob + nums[i];
        no_rob = MAX(rob, no_rob);
        rob = tmp;
    }
    return MAX(rob, no_rob);
}
