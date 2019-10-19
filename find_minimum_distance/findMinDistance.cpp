// return -1, if min distance > 100000000
// reutrn -2, if no adjacent indeces exist;
// otherwise return min dist

int findMin(vector<int>& nums) {
    if (nums.size() == 0) return -2;
    
    vector<pair<int, int>> vec(nums.size());
    vector<int> dp(nums.size(), INT_MAX);
    
    for (int i = 0; i < nums.size(); i++) {
        vec[i] = {nums[i], i};
    }
    sort(vec.begin(), vec.end());
    for (int i = 1; i < vec.size(); i++) {
        if (abs(vec[i].second - vec[i-1].second) == 1)
            dp[i] = min(dp[i-1], abs(vec[i].first - vec[i-1].first));
        else
            dp[i] = dp[i-1];
    }
    if (dp.back() / 100000000 > 0)
        return -1;
    if (dp.back() == INT_MAX)
        return -2;
    return dp.back();
}

int main() {
    vector<int> nums = {0, 1, 3, 3, 3, 5, 7, 11};
    cout << findMin(nums) << endl;
}
