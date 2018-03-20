class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        int counts[26] = {0};
        
        for (int i = 0; i < s.size(); i++) {
            counts[s[i] - 'a']++;
            counts[t[i] - 'a']--;
        }
        
        for (int i = 0; i < 26; i++) {
            if (counts[i]) return false;
        }
        return true;
    }
    
    bool isAnagram2(string s, string t) {
        if (s.size() != t.size()) return false;
    
        int m = 0, n = 0;
        for (int i = 0; i < s.size(); i++) {
            m ^= s[i];
            n ^= t[i];
        }
        /*
        for (auto c : s) {
            m ^= c;
        }
        for (auto c : t) {
            n ^= c;
        } */
        return m == n;
    }
};
