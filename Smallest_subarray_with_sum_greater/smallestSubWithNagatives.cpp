/*
這題 「最小長度子陣列，總和 > x（允許負數）」
不能用 sliding window，必須改用 Prefix Sum + Monotonic Deque
（這其實就是 LeetCode 862 的核心解法）。

為什麼負數會破壞 sliding window？

因為：

加進負數 → 總和可能變小

移動左指標不再「單調改善」

👉 雙指標失效

正確解法：Prefix Sum + 單調遞增 Deque

關鍵技巧

Deque 中維持 prefix 值單調遞增

前面可用就用（縮短長度）

後面比我大就踢掉（保持單調）
*/

#include <iostream>
#include <vector>

using namespace std;

int minSubArrayLenWithNegatives(vector<int>& nums, int x) {
    int n = nums.size();
    vector<long long> prefix(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        prefix[i+1] = prefix[i] + nums[i];
    }
    
    deque<int> dq;
    int res = INT_MAX;
    
    for (int i = 0; i <= n; i++) {
        // 條件 1：前面可以形成合法區間
        while (!dq.empty() && prefix[i] - prefix[dq.front()] > x) {
            res = min(res, i - dq.front());
            dq.pop_front();
        }
        
        // 條件 2：維持 prefix 單調遞增
        while (!dq.empty() && prefix[i] <= prefix[dq.back()]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    
    return res == INT_MAX ? -1 : res;
}

int main() {
    vector<int> nums = {1, -1, 5, -2, 3};
    int x = 3;
    cout << minSubArrayLenWithNegatives(nums, x) << endl;
    return 0;
}
