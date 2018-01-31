#define MIN(a, b) (((a)<(b))?(a):(b))
#define MAX(a, b) (((a)>(b))?(a):(b))

int maxProfit(int* prices, int pricesSize) {
    int i, min_price, max_profit;
    if (pricesSize < 1) return 0;
    
    min_price = prices[0];
    max_profit = 0;
    for (i = 1; i < pricesSize; i++) {
        min_price = MIN(min_price, prices[i]);
        max_profit = MAX(max_profit, prices[i] - min_price);
    }
    return max_profit;
}
