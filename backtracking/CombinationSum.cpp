void backtrack(vector<int>& candidates, vector<vector<int>>& res, vector<int>& nums, int target, int start) {
        if (!target) {
            res.push_back(nums);
            return;
        }
        for (int i = start; i < candidates.size() && target >= candidates[i]; i++) {
            nums.push_back(candidates[i]);
            backtrack(candidates, res, nums, target - candidates[i], i);  // not i + 1 because we can reuse same elements
            nums.pop_back();
        }
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> nums;
        sort(candidates.begin(), candidates.end());
        backtrack(candidates, res, nums, target, 0);
        return res;
}
