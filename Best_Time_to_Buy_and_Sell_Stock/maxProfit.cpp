class Solution {
public:
    int maxProfit1(vector<int>& prices) {
        int length = prices.size();
        if (length <= 1) return 0;
        
        int min_price = prices[0];
        int max_profit = 0;
        for (int i = 1; i < length; i++) {
            min_price = min(min_price, prices[i]);
            max_profit = max(max_profit, prices[i] - min_price);
        }
        return max_profit;
    }
    
    int maxProfit2(vector<int>& prices) {
        int length = prices.size();
        if (length <= 1) return 0;
        
        vector<int> gains(length -1, 0);
        for (int i = 1; i < length; i++) {
            gains[i - 1] = prices[i] - prices[i - 1];
        }
        return max(0, maxSubArray2(gains));
    }
    
    int maxSubArray1(vector<int>& nums) {
        vector<int> f(nums.size());
        f[0] = nums[0];
        
        for (int i = 1; i < nums.size(); ++i)
            f[i] = max(f[i - 1] + nums[i], nums[i]);
        
        return *std::max_element(f.begin(), f.end());
    }
    
    int maxSubArray2(vector<int>& gains) {
        int sum = gains[0];
        int _max = gains[0];
        
        for (int i = 1; i < gains.size(); i++) {
            sum = max(gains[i], gains[i] + sum);
            if (sum > _max) _max = sum;
        }
        return _max;
    }
};
