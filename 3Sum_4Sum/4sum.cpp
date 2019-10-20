vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> res;
    if (nums.size() < 4) return res;
    
    sort(nums.begin(), nums.end());
    
    for (int i = 0; i < nums.size() - 3; i++) {
        if (i > 0 && nums[i] == nums[i-1]) continue;
        for (int j = i + 1; j < nums.size() - 2; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;
            int third = j + 1, four = nums.size() - 1;
            while (third < four) {
                int sum = nums[i] + nums[j] + nums[third] + nums[four];
                if (sum < target)
                    third++;
                else if (sum > target)
                    four--;
                else {
                    vector<int> m = {nums[i], nums[j], nums[third], nums[four]};
                    res.push_back(m);
                    while (third < four && nums[third] == nums[third+1]) third++;
                    while (third < four && nums[four] == nums[four-1]) four--;
                }
            }
        }
    }
    return res;
}
