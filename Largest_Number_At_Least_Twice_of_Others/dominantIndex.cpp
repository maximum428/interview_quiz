class Solution {
public:
    int dominantIndex(vector<int>& nums) {
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
};
