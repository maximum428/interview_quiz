class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> counts;
        vector<int> res;
        
        for (int i = 0; i < nums2.size(); i++)
            ++counts[nums2[i]];
        for (int i = 0; i < nums1.size(); i++) {
            if (counts.find(nums1[i]) != counts.end() && --counts[nums1[i]] >= 0)
                res.push_back(nums1[i]);
        }
        return res;
    }
};
