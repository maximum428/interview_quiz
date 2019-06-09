int longestMountain(vector<int>& nums) {
    vector<int> inc(nums.size());
    vector<int> dec(nums.size());
    
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] > nums[i - 1]) inc[i] = inc[i - 1] + 1;
    }
    for (int i = nums.size() - 2; i > 0; i--) {
        if (nums[i] > nums[i + 1]) dec[i] = dec[i + 1] + 1;
    }
    int ans = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (inc[i] && dec[i])
            ans = max(ans, inc[i] + dec[i] + 1);
    }
    return ans >= 3 ? ans : 0;
}

int main() {
    vector<int> vec = {2, 1, 4, 7, 3, 2, 5};
    cout << longestMountain(vec) << endl;
}
