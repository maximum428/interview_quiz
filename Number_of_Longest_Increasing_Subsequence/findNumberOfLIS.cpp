class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        vector<int> count(n, 1);
        vector<int> length(n, 1);
        
        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++)
                if (nums[i] > nums[j]) {
                    if (length[j] + 1 > length[i]) {
                        length[i] = length[j] + 1;
                        count[i] = count[j];
                    } else if (length[j] + 1 == length[i])
                        count[i] += count[j];
                }
        
        int max_len = *max_element(length.begin(), length.end());
        
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (length[i] == max_len)
                ans += count[i];
        }
        return ans;
    }
};
