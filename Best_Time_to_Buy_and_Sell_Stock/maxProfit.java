class Solution {
    public int maxProfit(int[] prices) {
        if (prices.length < 1) return 0;
        int min_price = prices[0];
        int max_profit = 0;
        for (int i = 1; i < prices.length; i++) {
            min_price = Math.min(min_price, prices[i]);
            max_profit = Math.max(max_profit, prices[i] - min_price);
        }
        return max_profit;
    }
}
