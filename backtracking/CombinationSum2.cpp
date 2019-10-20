void backtrack(vector<int>& candidates, vector<vector<int>>& res, vector<int>& nums, int target, int start) {
        if (!target) {
            res.push_back(nums);
            return;
        }
        for (int i = start; i < candidates.size() && target >= candidates[i]; i++) {
            if (i == start || candidates[i] != candidates[i-1]) {
                nums.push_back(candidates[i]);
                backtrack(candidates, res, nums, target - candidates[i], i+1);
                nums.pop_back();
            }
        }
    }
    
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> nums;
        sort(candidates.begin(), candidates.end());
        backtrack(candidates, res, nums, target, 0);
        return res;
    }
