#include <iostream>
#include <vector>

using namespace std;

bool isInvalid(vector<vector<int>>& res, int r, int c) {
  if (r < 0 || c < 0 || r >= (int)res.size() || c >= (int)res.size() || res[r][c] != 0) {
      return true;
  }
  return false;
}
vector<vector<int>> getSpiral(int n) {
  if (n <= 0) return {{}};

  vector<int> v(n, 0);
  vector<vector<int>> res(n, v); //(n, vector<int>(n, 0));
  vector<int> dc = {1, 0, -1, 0};
  vector<int> dr = {0, 1, 0, -1};
  int dir = 0, val = 0, r = 0, c = 0, limit = n * n;
  while (val++ < limit) {
      res[r][c] = val;
      r += dr[dir];
      c += dc[dir];
      if (isInvalid(res, r, c)) {
        r -= dr[dir];
        c -= dc[dir];
        dir = (dir + 1) % 4;
        r += dr[dir];
        c += dc[dir];
      }
   }
   return res;
}

// To execute C++, please define "int main()"
int main() {
  auto vec = getSpiral(8);
  for (const auto& v : vec) {
    for (const auto &n : v) {
      cout << n << "\t";
    }
    cout << "\n";
  }
  return 0;
}
