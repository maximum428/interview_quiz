class Solution {
    public int rob(int[] nums) {
        if (nums.length == 0) return 0;
        if (nums.length == 1) return nums[0];
        int rob_robf = nums[0], rob_nrobf = 0, nrob_robf = 0, nrob_nrobf = 0; // initialize from first house
        
        for (int i = 1; i < nums.length; i++) {
            int tmp = nrob_robf + nums[i];
            nrob_robf = Math.max(rob_robf, nrob_robf);
            rob_robf = tmp;
            
            tmp = nrob_nrobf + nums[i];
            nrob_nrobf = Math.max(rob_nrobf, nrob_nrobf);
            rob_nrobf = tmp;
        }
        return Math.max(rob_nrobf, nrob_robf);
    }
}
