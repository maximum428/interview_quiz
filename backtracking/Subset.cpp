#if 1
    void backtrack(vector<int>& nums, vector<vector<int>>& res, vector<int>& vec, int start) {
        res.push_back(vec);
        for (int i = start; i < nums.size(); i++) {
            vec.push_back(nums[i]);
            backtrack(nums, res, vec, i+1);
            vec.pop_back();
        }
    }
    
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> vec;
        sort(nums.begin(), nums.end());
        backtrack(nums, res, vec, 0);
        return res;
    }
#else
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res = {{}};
        
        for (auto num : nums) {
            int n = res.size();
            cout << "num: " << num << "; size: " << n << endl;
            for (int i = 0; i < n; i++) {
                cout << "i: " << i << endl;
                res.push_back(res[i]);
                res.back().push_back(num);
                //print(res);
            }
        }
        return res;
    }
#endif
