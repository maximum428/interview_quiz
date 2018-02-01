class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        
        int rob_robf = nums[0], rob_nrobf = 0, nrob_robf = 0, nrob_nrobf = 0;
        
        for (int i = 1; i < nums.size(); i++) {
            int tmp = nrob_robf + nums[i];
            nrob_robf = max(rob_robf, nrob_robf);
            rob_robf = tmp;
            
            tmp = nrob_nrobf + nums[i];
            nrob_nrobf = max(rob_nrobf, nrob_nrobf);
            rob_nrobf = tmp;
        }
        return max(rob_nrobf, nrob_robf);
    }
};
