#include <iostream>

int minFlipMonoIncr(string s) {
    int n = s.length();
    vector<vector<int>> dp(n+1, vector<int>(2));
    
    dp[0][0] = 0;
    dp[0][1] = 1;
    for (int i = 1; i <= n; i++) {
        if (s[i-1] == '0') {
            dp[i][0] = dp[i - 1][0];
            dp[i][1] = min(dp[i - 1][1], dp[i - 1][0]) + 1;
        } else {
            dp[i][0] = dp[i - 1][0] + 1;
            dp[i][1] = min(dp[i - 1][1], dp[i - 1][0]);
        }
    }
    return min(dp[n][0], dp[n][1]);
}

int minFlipMonoIncr2(string s) {
    const int n = s.size();
    vector<int> l(n + 1);  // 1 -> 0;
    vector<int> r(n + 1); // 0 -> 1;
    l[0] = s[0] - '0';
    r[n - 1] = '1' - s[n - 1];
    
    for (int i = 1; i < n; i++)
        l[i] = l[i - 1] + s[i] - '0';
    for (int i = n - 2; i >= 0; i--)
        r[i] = r[i + 1] + '1' - s[i];
    
    int ans = r[0];
    for (int i = 1; i <= n; i++)
        ans = min(ans, l[i - 1] + r[i]);
    return ans;
}

int minFlipsMonoIncr(string S) {
    vector<int> flipOne_zero(S.length(), INT_MAX);
    vector<int> flipZero_one(S.length(), INT_MAX);
        
    flipOne_zero[0] = S[0] == '1' ? 1 : 0;
    flipZero_one[0] = S[0] == '1' ? 0 : 1;
        
    for (int i = 1; i < S.length(); i++) {
        if (S[i] == '1') {
            flipZero_one[i] = min(flipOne_zero[i-1], flipZero_one[i-1]);
            flipOne_zero[i] = 1 + flipOne_zero[i-1];
        } else {
            flipOne_zero[i] = flipOne_zero[i-1];   // min(flipZero_one[i], flipOne_zero[i-1]);
            flipZero_one[i] = 1+ flipZero_one[i-1];
        }
    }
    return min(flipZero_one.back(), flipOne_zero.back());
}

int main() {
    string s = "00011000";
    cout << minFlipMonoIncr(s) << endl;
    return 0;
}
