class Solution {
public:
    int rob(vector<int>& nums) {
        int rob = 0;
        int no_rob = 0;
        
        for (auto num : nums) {
            int tmp = max(rob, no_rob);
            rob = no_rob + num;
            no_rob = tmp;
        }
        return max(rob, no_rob);
    }
};
