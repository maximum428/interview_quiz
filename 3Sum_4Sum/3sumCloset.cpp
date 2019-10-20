int threeSumCloset(vector<int>& nums, int target) {
    if (nums.size() < 3) return 0;
    
    int closet = nums[0] + nums[1] + nums[2];
    sort(nums.begin(), nums.end());
    
    for (int i = 0; i < nums.size() - 2; i++) {
        int second = i + 1;
        int third = nums.size() - 1;
        
        while (second < third) {
            int sum = nums[i] + nums[second] + nums[third];
            if (sum == target)
                return sum;
            if (abs(target-sum) < abs(target-closet))
                closet = sum;
            else if (sum < target)
                second++;
            else third--;
        }
    }
    return closet;
}
