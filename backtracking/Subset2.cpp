void backtrack(vector<int>& nums, vector<vector<int>>& res, vector<int>& vec, int start) {
        res.push_back(vec);
        for (int i = start; i < nums.size(); i++) {
            if (i > start && nums[i] == nums[i-1]) continue;
            vec.push_back(nums[i]);
            backtrack(nums, res, vec, i+1);
            vec.pop_back();
        }
    }
    
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> vec;
        sort(nums.begin(), nums.end());
        backtrack(nums, res, vec, 0);
        return res;
    }
