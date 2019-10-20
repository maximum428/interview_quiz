void helper(vector<vector<int>>& res, vector<int>& vec, int k, int start, int n) {
        if (vec.size() == k && n == 0) {
            res.push_back(vec);
            return;
        }
        for (int i = start; i <= 9; i++) {
            vec.push_back(i);
            helper(res, vec, k, i+1, n-i);
            vec.pop_back();
        }
}
vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        vector<int> vec;
        
        helper(res, vec, k, 1, n);
        return res;
}
