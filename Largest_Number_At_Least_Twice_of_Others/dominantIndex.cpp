class Solution {
public:
    int dominantIndex1(vector<int>& nums) {
        int maxOne = 0, maxTwo = 0, index;
        
        for (int i = 0; i < nums.size(); i++) {
            if (maxOne < nums[i]) {
                maxTwo = maxOne;
                maxOne = nums[i];
                index = i;
            } else if (maxTwo < nums[i]) {
                maxTwo = nums[i];
            }
        }
        return maxOne >= maxTwo * 2 ? index : -1;
    }
    
    int dominantIndex2(vector<int>& nums) {
        if (nums.size() <= 1) return -1;
        vector<int>::iterator max_elm = max_element(nums.begin(), nums.end());
        int index = distance(nums.begin(), max_elm);
        for (int i = 0; i < nums.size(); i++) {
            if (i != index && nums[i]*2 > *max_elm)
                return -1;
        }
        return index;
    }
};
