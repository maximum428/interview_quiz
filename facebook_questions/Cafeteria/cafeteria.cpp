#include <bits/stdc++.h>

using namespace std;

long long getMaxAdditinalDinersCount(long long N, long long K, int M, vector<long long> S) {
  long long res = 0;
  sort(S.begin(), S.end());

  res += (S[0] - 1) / (K+1);
  for (int i = 1; i < S.size(); i++) {
    res += (S[i] - S[i-1] - (K+1)) / (K+1);
  }
  res += (N - S[S.size()-1]) / (K+1);
  return res;
}
====================================================================

  long long maxAdditionalDiners(long long N, long long K, vector<long long>& S) {
    //if (S.empty()) return (N + K) / (K + 1);

    sort(S.begin(), S.end());
    long long ans = 0;

    // 左側空間
    long long left = S[0] - K - 1;
    if (left > 0) ans += (left + K) / (K + 1);

    // 中間空間
    for (size_t i = 1; i < S.size(); i++) {
        long long gap = S[i] - S[i-1] - 2*K - 1;
        if (gap > 0) ans += (gap + K) / (K + 1);
    }

    // 右側空間
    long long right = N - S.back() - K;
    if (right > 0) ans += (right + K) / (K + 1);

    return ans;
}

int main() {
    long long N = 10, K= 1;
    vector<long long> seats = {2, 6};
    
    cout << maxAdditionalDiners(N, K, seats) << endl;
    return 0;
}
