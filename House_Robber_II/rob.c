#define MAX(a, b) (((a)>(b))?(a):(b))

int rob(int* nums, int numsSize) {
    int i, rob_robf, rob_nrobf = 0, nrob_robf = 0, nrob_nrobf = 0;
    if (numsSize == 0) return 0;
    if (numsSize == 1) return nums[0];
    
    rob_robf = nums[0];
    for (i = 1; i < numsSize; i++) {
        int tmp = rob_nrobf + nums[i];
        rob_nrobf = MAX(rob_robf, rob_nrobf);
        rob_robf = tmp;
        
        tmp = nrob_nrobf + nums[i];
        nrob_nrobf = nrob_robf > nrob_nrobf ? nrob_robf : nrob_nrobf;
        nrob_robf = tmp;
    }
    return rob_nrobf > nrob_robf ? rob_nrobf : nrob_robf;
}
