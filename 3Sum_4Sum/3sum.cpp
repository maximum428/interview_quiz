vector<vector<int>> threeSum(vector<int> &nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    
    for (int i = 0; i < nums.size(); i++) {
        int first = -nums[i];
        int second = i + 1;
        int third = nums.size() - 1;
        while (second < third) {
            int sum = nums[second] + nums[third];
            if (sum > first) 
                third--;
            else if (sum < first)
                second++
            else {
                vector<int> m = {nums[i], nums[second], nums[third]};
                res.push_back(m);
                while (second < third && nums[second] == m[1]) second++;
                while (second < third && nums[third] == m[2]) third--;
            }
        }
        while (i+1 < nums.size() && nums[i+1] == nums[i]) i++;
    }
    return res;
}

// solution #2 by using backtrack algorithm
void backtrack(vector<int>& nums, vector<vector<int>>& res, vector<int>& vec, int amount, int start) {
   if (amount == 0 && vec.size() == 3) {
       res.push_back(vec);
       return;
   }
   for (int i = start; i < (int)nums.size(); i++) {
      if (i > start && nums[i] == nums[i-1]) continue;
         vec.push_back(nums[i]);
         backtrack(nums, res, vec, nums[i]+amount, i+1);
         vec.pop_back();
   }
}

vector<vector<int>> threeSum(vector<int> nums) {
    vector<vector<int>> res;
    vector<int> vec;
    sort(nums.begin(), nums.end());
    backtrack(nums, res, vec, 0, 0);
    return res;
}
