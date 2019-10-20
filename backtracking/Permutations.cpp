void backtrack(vector<int>& nums, vector<vector<int>>& res, vector<int>& vec, int start) {
        if (vec.size() == nums.size()) {
            res.push_back(vec);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if (find(vec.begin(), vec.end(), nums[i]) != vec.end())
                continue;
            vec.push_back(nums[i]);
            backtrack(nums, res, vec, i+1);
            vec.pop_back();
        }
}

vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> vec;
        sort(nums.begin(), nums.end());
        
        backtrack(nums, res, vec, 0);
        return res;
}
