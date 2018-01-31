class Solution {
public:
    int maxSubArray1(vector<int>& nums) {
        vector<int> f(nums.size());
        f[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            f[i] = max(nums[i] + f[i - 1], nums[i]);
        }
        return *std::max_element(f.begin(), f.end());
    }
    
    int maxSubArray2(vector<int>& nums) {
        int m = nums[0];
        int sum = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            sum = max(nums[i] + sum, nums[i]);
            m = max(m, sum);
        }
        return m;
    }
};
