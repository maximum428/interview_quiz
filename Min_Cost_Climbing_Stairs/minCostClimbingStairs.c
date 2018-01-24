#include<stdio.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int minCostClimbingStairs_1(const int *cost, const int size) {
    int dp[size], i;
    for (i = 0; i < size; i++) {
        dp[i] = INT_MAX;
    }
    
    dp[0] = *cost;
    dp[1] = *(cost + 1);
    for (int i = 2; i < size; i++) {
        dp[i] = MIN(dp[i - 1], dp[i - 2]) + cost[i];
    }
    return MIN(dp[10 - 1], dp[10 - 2]);
}

int minCostClimbingStairs_2(const int *cost, const int size) {
    int dp[size + 1], i;
    for (i = 0; i < size; i++) {
        dp[i] = 0;
    }
    
    for (i = 2; i <= size; i++) {
        dp[i] = MIN(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
    }
    return dp[size];
}

int minCostClimbingStairs_3(const int *cost, const int size) {
    int dp1 = 0, dp2 = 0, i;
    for (i = 2; i <= size; i++) {
        int dp = MIN(dp1 + cost[i - 1], dp2 + cost[i - 2]);
        dp2 = dp1;
        dp1 = dp;
    }
    return dp1;
}

int minCostClimbingStairs_4(const int *cost, const int size) {
    int m[size + 1], i;
    for (i = 0; i <= size; i++) {
        m[i] = 0;
    }
    return MIN(dp_1(cost, m, size - 1),
               dp_1(cost, m, size - 2));
}

int dp_1(int *cost, int *m, int i) {
    if (i < 0) return 0;
    if (m[i] > 0) return m[i];
    return m[i] = MIN(dp_1(cost, m, i - 1),
                      dp_1(cost, m, i - 2)) + cost[i];
}

int minCostClimbingStairs_5(const int *cost, const int size) {
    int m[size + 1], i;
    for (i = 0; i <= size; i++) {
        m[i] = 0;
    }
    return dp_2(cost, m, size);
}

int dp_2(int *cost, int *m, int i) {
    if (i <= 1) return 0;
    if (m[i] > 0) return m[i];
    return m[i] = MIN(dp_2(cost, m, i - 1) + cost[i - 1],
                      dp_2(cost, m, i - 2) + cost[i - 2]);
}

int main(void) {
    int cost[10] = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    //printf("%d\n", minCostClimbingStairs_1(&cost, sizeof(cost)/sizeof(cost[0])));
    //printf("%d\n", minCostClimbingStairs_2(&cost, sizeof(cost)/sizeof(cost[0])));
    //printf("%d\n", minCostClimbingStairs_3(&cost, sizeof(cost)/sizeof(cost[0])));
    //printf("%d\n", minCostClimbingStairs_4(&cost, sizeof(cost)/sizeof(cost[0])));
    printf("%d\n", minCostClimbingStairs_5(&cost, sizeof(cost)/sizeof(cost[0])));
    return 0;
}
