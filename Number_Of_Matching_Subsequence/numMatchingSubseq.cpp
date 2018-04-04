class Solution {
public:
    int numMatchingSubseq1(string S, vector<string>& words) {
        vector<vector<int>> pos(128);
        for (int i = 0; i < S.length(); i++)
            pos[S[i]].push_back(i);
        int ans = 0;
        for (const string& word : words)
            ans += isMatch1(word, pos);
        return ans;
    }
    
    int numMatchingSubseq2(string S, vector<string>& words) {
        map<char, vector<int>> pos;
        for (int i = 0; i < S.length(); i++)
            pos[S[i]].push_back(i);
        
        int ans = 0;
        for (auto word : words)
            ans += isMatch2(word, pos);
        return ans;
    }
    
private:
    unordered_map<string, bool> m_;
    bool isMatch1(const string& word, const vector<vector<int>>& pos) {
        if (m_.count(word)) return m_[word];
        int last_index = -1;
        for (const char c : word) {
            const vector<int>& p = pos[c];
            const auto it = std::lower_bound(p.begin(), p.end(), last_index + 1);
            if (it == p.end()) return m_[word] = false;
            last_index = *it;
        }
        return m_[word] = true;
    }
    
    bool isMatch2(const string& word, map<char, vector<int>>& pos) {
        int last_index = -1;
        for (auto c : word) {
            const vector<int>& p = pos[c];
            const auto it = lower_bound(p.begin(), p.end(), last_index + 1);
            if (it == p.end()) return false;
            last_index = *it;
        }
        return true;
    }
};
