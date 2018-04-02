class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int majority = nums[0];
        int res = nums.size() / 2;
        unordered_map<int, int> counts;
                                            
        if (nums.size() == 0) throw invalid_argument("Error: Incorrect data");
        
        for (int i = 0; i < nums.size(); i++) {
            if (++counts[nums[i]] > res)
                return nums[i];
        }
        return majority;
    }
};
