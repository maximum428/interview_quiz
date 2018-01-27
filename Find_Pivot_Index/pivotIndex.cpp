class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int sum = 0, sub_sum = 0;
        
        for (auto x : nums) sum += x;
        
        for (int i = 0; i < nums.size(); i++) {
            if (sub_sum == sum - nums[i] - sub_sum) return i;
            sub_sum += nums[i];
        }
        return -1;
    }
};
