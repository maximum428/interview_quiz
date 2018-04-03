int maximalSquare(vector<vector<int>>& matrix) {
   if (matrix.size() == 0) return 0;
   int m = matrix.size();
   int n = matrix[0].size();
   int res = 0;
   vector<vector<int>> dp(m+1, vector<int>(n+1));
   for (int i = 1; i <= m; i++) {
       for (int j = 1; j <= n; j++) {
           if (matrix[i - 1][j - 1] == 1) {
               dp[i][j] = min(min(dp[i][j - 1], dp[i - 1][j - 1]), dp[i - 1][j]) + 1;
               res = max(res, dp[i][j]);
           }
       }
   }
   return res * res;
}
    
int main() {
   vector<vector<int>> matrix = {{1, 0, 1, 0, 0},
                                  {1, 0, 1, 1, 1},
                                  {1, 1, 1, 1, 1},
                                  {1, 0, 0, 1, 0}};
    
    cout << maximalSquare(matrix) << endl;
}
