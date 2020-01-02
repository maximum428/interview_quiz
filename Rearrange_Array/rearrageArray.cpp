void rearrange(vector<int>& nums) {
    if (*max_element(nums.begin(), nums.end()) != nums.size()-1) return;
    vector<bool> visited(nums.size());
    
    int idx = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (!visited[nums[i]]) {
            visited[nums[i]] = true;
            nums[nums[i]] = nums[i];
            idx = 1;
        }
    }
    for (int i = 0; i < visited.size(); i++) {
        if (!visited[i])
            nums[i] = i;
    }
}

int main() {
    vector<int> nums = {2, 1, 0, 3};
    rearrange(nums);
    
    for (auto n : nums)
        cout << n << ", ";
    cout << "\n";
}
