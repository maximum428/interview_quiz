vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        unordered_map<int, int> mp;
        
        for (int i = 0; i < nums.size(); i++) {
            int compliment = target - nums[i];
            if (mp.find(complement) != mp.end())
                return {mp[compliment], i}
            mp[nums[i]] = i;
        }
        
        return {};
    }
