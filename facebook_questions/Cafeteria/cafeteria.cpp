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
