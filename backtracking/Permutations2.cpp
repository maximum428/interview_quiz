void backtrack(vector<int>& nums, vector<vector<int>>& res, vector<int>& vec, vector<int>& visited) {
        if (vec.size() == nums.size()) {
            res.push_back(vec);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if(visited[i] || i > 0 && nums[i] == nums[i-1] && !visited[i - 1]) continue;
            visited[i] = 1;
            vec.push_back(nums[i]);
            backtrack(nums, res, vec, visited);
            visited[i] = 0;
            vec.pop_back();
        }
    }
    
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> vec;
        vector<int> visited(nums.size());
        sort(nums.begin(), nums.end());
        backtrack(nums, res, vec, visited);
        return res;
    }
