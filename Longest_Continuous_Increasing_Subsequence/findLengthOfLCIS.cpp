class Solution {
public:
    int findLengthOfLCIS1(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        
        int ans = INT_MIN, count = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] <= nums[i - 1]) {
                ans = max(ans, count);
                count = 1;
            } else
                count++;
        }
        return max(ans, count);
    }
    
    int findLengthOfLCIS2(vector<int>& nums) {
      int ans = 0, start = 0;
      for (int i = 0; i < nums.size(); ++i) {
        if (i > 0 && nums[i] <= nums[i - 1])
          start = i;
        ans = max(ans, i - start + 1);
      }
      return ans;
    }
};
