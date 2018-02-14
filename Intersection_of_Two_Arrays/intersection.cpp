class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        set<int> s(nums2.begin(), nums2.end());
        vector<int> out;
        
        for (auto const& x : nums1) {
            if (s.erase(x))
                out.push_back(x);
        }
        return out;
    }
};
