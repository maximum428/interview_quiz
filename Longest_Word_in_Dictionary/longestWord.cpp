#include <iostream>
/*
Output sample:
1. return the longest work with the smallest lexicographical order if more answer.
2. return empty string if no answer.
*/
class Solution {
public:
    string longestWord(vector<string>& words) {
        sort(words.begin(), words.end());
        unordered_set<string> built;
        string res;
        for (auto const& w : words) {
            if (w.size() == 1 || built.count(w.substr(0, w.size() - 1))) {
                cout << "w: " << w << "; res: " << res << "; w size: " << w.size() << "; res size: " << res.size() << endl;
                res = w.size() > res.size() ? w : res;
                built.insert(w);
            }
        }
        return res;
    }
};

int main() {
    vector<string> vec = {"a", "banana", "app", "appl", "ap", "apply", "apple"};
    Solution solution;
    cout << solution.longestWord(vec) << endl;
}
