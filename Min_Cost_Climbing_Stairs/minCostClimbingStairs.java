public class Solution {
    public int minCostClimbingStairs_1(int[] cost) {
        final int n = cost.length;
        int[] dp = new int[n];
        Arrays.fill(dp, Integer.MAX_VALUE);

        dp[0] = cost[0];
        dp[1] = cost[1];
        for (int i = 2; i < n; i++) {
            dp[i] = Math.min(dp[i - 1], dp[i - 2]) + cost[i];
        }
        return Math.min(dp[n - 1], dp[n - 2]);
    }
    
    public int minCostClimbingStairs_2(int[] cost) {
        int[] dp = new int[cost.length + 1];
        Arrays.fill(dp, 0);
        
        for (int i = 2; i <= cost.length; i++) {
            dp[i] = Math.min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i -2]);
        }
        return dp[cost.length];
    }
    
    public int minCostClimbingStairs_3(int[] cost) {
        int dp1 = 0, dp2 = 0;
        for (int i = 2; i <= cost.length; i++) {
            int dp = Math.min(dp1 + cost[i - 1], dp2 + cost[i - 2]);
            dp2 = dp1;
            dp1 = dp;
        }
        return dp1;
    }
    
    public int minCostClimbingStairs_4(int[] cost) {
        int[] m = new int[cost.length + 1];
        return Math.min(dp_1(cost, m, cost.length - 1),
                        dp_1(cost, m, cost.length - 2));
    }
    
    public int minCostClimbingStairs_5(int[] cost) {
        int[] m = new int[cost.length + 1];
        return dp_2(cost, m, cost.length);
    }
    
    private int dp_1(int[] cost, int[] m, int i) {
        if (i < 0) return 0;
        if (m[i] > 0) return m[i];
        return m[i] = Math.min(dp_1(cost, m, i - 1),
                               dp_1(cost, m, i - 2)) + cost[i];
    }
    
    private int dp_2(int[] cost, int[] m, int i) {
        if (i <= 1) return 0;
        if (m[i] > 0) return m[i];
        return m[i] = Math.min(dp_2(cost, m, i - 1) + cost[i - 1],
                               dp_2(cost, m, i - 2) + cost[i - 2]);
    }
    
    public static void main(String[] args) {
        int[] cost = new int[] {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
        Solution solution = new Solution();
        //System.out.println(solution.minCostClimbingStairs_1(cost));
        //System.out.println(solution.minCostClimbingStairs_2(cost));
        //System.out.println(solution.minCostClimbingStairs_3(cost));
        //System.out.println(solution.minCostClimbingStairs_4(cost));
        System.out.println(solution.minCostClimbingStairs_5(cost));
    }
}
