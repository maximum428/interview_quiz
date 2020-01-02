void rearrange(vector<int>& nums) {
#if 1
    if (*max_element(nums.begin(), nums.end()) != nums.size()-1) return;
    unordered_set<int> st;
    for (int i = 0; i < nums.size(); i++) {
        if (st.find(nums[i]) != st.end()) {
            cout << "duplicated element\n";
            return;
        }
        st.insert(nums[i]);
    }
    
    for (int i = 0; i < nums.size(); i++)
        nums[i %nums.size()] = i % nums.size();
#else
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
#endif
}

int main() {
    vector<int> nums = {2, 1, 0, 3};
    rearrange(nums);
    
    for (auto n : nums)
        cout << n << ", ";
    cout << "\n";
}
