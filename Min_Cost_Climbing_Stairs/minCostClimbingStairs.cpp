#include <iostream>

class Solution {
public:
    int minCostClimbingStairs_1(vector<int>& cost) {
        const int n = cost.size();
        vector<int> dp(n, INT_MAX);
        
        dp[0] = cost[0];
        dp[1] = cost[1];
        for (int i = 2; i < n; i++) {
            dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
        }
        return min(dp[n - 1], dp[n - 2]);
    }
    
    int minCostClimbingStairs_2(vector<int>& cost) {
        vector<int> dp(cost.size() + 1, 0);
        for (int i = 2; i <= cost.size(); i++) {
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }
        return dp[cost.size()];
    }
    
    int minCostClimbingStairs_3(vector<int>& cost) {   // O(1) space
        int dp1 = 0, dp2 = 0;
        for (int i = 2; i <= cost.size(); i++) {
            int dp = min(dp1 + cost[i-1], dp2 + cost[i-2]);
            dp2 = dp1;
            dp1 = dp;
        }
        return dp1;
    }
    
    int minCostClimbingStairs_4(vector<int>& cost) {
        vector<int> m(cost.size() + 1);
        return min(dp_1(cost, m, cost.size() - 1),
                   dp_1(cost, m, cost.size() - 2));
    }

    int minCostClimbingStairs_5(vector<int>& cost) {
        vector<int> m(cost.size() + 1);
        return dp_2(cost, m, cost.size());
    }
    
private:
    int dp_1(vector<int>& cost, vector<int>& m, int i) {
        if (i < 0) return 0;
        if (m[i] > 0) return m[i];
        return m[i] = min(dp_1(cost, m, i - 1), dp_1(cost, m, i - 2)) + cost[i];
    }
    
    int dp_2(vector<int>& cost, vector<int>& m, int i) {
        if (i <= 1) return 0;
        if (m[i] > 0) return m[i];
        return m[i] = min(dp_2(cost, m, i - 1) + cost[i - 1],
                          dp_2(cost, m, i - 2) + cost[i - 2]);
    }
};

int main() {
    vector<int> cost = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    Solution solution;
    //cout << solution.minCostClimbingStairs_2(cost) << endl;
    //cout << solution.minCostClimbingStairs_2(cost) << endl;
    //cout << solution.minCostClimbingStairs_3(cost) << endl;
    //cout << solution.minCostClimbingStairs_4(cost) << endl;
    cout << solution.minCostClimbingStairs_5(cost) << endl;
}
