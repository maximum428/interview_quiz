int threeSumSmaller(vector<int>& nums, int target) {
    int (nums.size() < 3) return 0;
    sort(nums.begin(), nums.end());
    int count = 0;
    
    for (int i = 0; i < nums.size() - 2; i++) {
        int second = i + 1;
        int third = nums.size() - 1;
        
        while (second < third) {
            int sum = nums[i] + nums[second] + nums[third];
            if (sum < target) count += (third - second++);
            else third--;
        }
    }
    return count;
}
