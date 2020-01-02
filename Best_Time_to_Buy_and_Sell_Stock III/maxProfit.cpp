class Solution {
public:
    int maxProfit(vector<int>& prices) {
#if 1
#if 1
        if (prices.size() == 0) return 0;
        vector<int> leftProfit(prices.size());
        vector<int> rightProfit(prices.size());
        
        leftProfit[0] = 0;
        int min_price = prices[0];
        for (int i = 1; i < prices.size(); i++) {
            min_price = min(min_price, prices[i]);
            leftProfit[i] = max(leftProfit[i-1], prices[i] - min_price);
        }

        rightProfit[prices.size()-1] = 0;
        int max_price = prices[prices.size() -1];
        for (int i = prices.size() - 2; i >= 0; i--) {
            max_price = max(max_price, prices[i]);
            rightProfit[i] = max(rightProfit[i+1], max_price - prices[i]);
        } 

        int maxProfit = 0;
        for (int i = 0; i < prices.size(); i++) {
            maxProfit = max(maxProfit, leftProfit[i] + rightProfit[i]);
        }
        return maxProfit;
#else
        if (prices.size() == 0) return 0;
        int dp1[3] = {0}, dp2[3] = {0};
        for (int i = 0; i < prices.size() - 1; i++) {
            int diff = prices[i + 1] - prices[i];
            for (int j = 2; j >= 1; j--) {
                dp2[j] = max(dp1[j - 1] + max(diff, 0), dp2[j] + diff);
                dp1[j] = max(dp2[j], dp1[j]);
            }
        }
        return dp1[2];
#endif
#else
#if 1
        int oneBuy = INT_MAX, twoBuy = INT_MAX;
        int oneSell = 0, twoSell = 0;
        
        for (int i = 0; i < prices.size(); i++) {
            int price = prices[i];
            oneBuy = min(oneBuy, price);
            oneSell = max(oneSell, price - oneBuy);
            twoBuy = min(twoBuy, price - oneSell);
            twoSell = max(twoSell, price - twoBuy);
        }
        return twoSell;
#else
        if (prices.size() == 0) return 0;
        int n = prices.size(), dp1[n][3] = {0}, dp2[n][3] = {0};
        for (int i = 1; i < prices.size(); i++) {
            int diff = prices[i] - prices[i - 1];
            for (int j = 1; j <= 2; j++) {
                dp2[i][j] = max(dp1[i - 1][j - 1] + max(diff, 0), dp2[i - 1][j] + diff);
                dp1[i][j] = max(dp2[i][j], dp1[i - 1][j]);
            }
        }
        return dp1[n - 1][2];
#endif
#endif
    }
};
