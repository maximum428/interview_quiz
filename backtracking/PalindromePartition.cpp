bool isPalindrome(string s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--])
                return false;
        }
        return true;
}
    
void backtrack(string s, vector<vector<string>>& res, vector<string>& vec, int start) {
        if (start == s.length()) {
            res.push_back(vec);
            return;
        }
        
        for (int i = start; i < s.length(); i++) {
            if (isPalindrome(s, start, i)) {
                vec.push_back(s.substr(start, i - start + 1));
                backtrack(s, res, vec, i+1);
                vec.pop_back();
            }
        }
}
    
vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> vec;
        
        backtrack(s, res, vec, 0);
        return res;
}
