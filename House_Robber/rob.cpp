class Solution {
public:
    int rob1(vector<int>& nums) {
        const int n = nums.size();
        m_ = vector<int>(n, -1);
        return rob1(nums, n - 1);
    }
    int rob2(vector<int>& nums) {
        int rob = 0;
        int no_rob = 0;
        
        for (auto num : nums) {
            int tmp = max(rob, no_rob);
            rob = no_rob + num;
            no_rob = tmp;
        }
        return max(rob, no_rob);
    }
    int rob3(vector<int>& nums) {
        if (nums.empty()) return 0;
        int dp2 = 0;
        int dp1 = 0;
        for (int i = 0; i < nums.size(); ++i) {
            int dp = max(dp2 + nums[i], dp1);
            dp2 = dp1;
            dp1 = dp;
        }
        return dp1;
    }
private:
    int rob1(const vector<int>& nums, int i) {
        if (i < 0) return 0;
        if (m_[i] >= 0) return m_[i];
        return m_[i] = max(rob(nums, i - 2) + nums[i], rob(nums, i - 1));
    }
    vector<int> m_;
};
