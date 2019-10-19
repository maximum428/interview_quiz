int LogestTurbulence(vector<int>& nums) {
    vector<pair<int,int>> up(nums.size()), down(nums.size());
    up[0] = {1, 0};
    down[0] = {1, 0};
    int up_max = 1, down_max = 1;
    
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] < nums[i-1]) {
            if (up[i-1].second < 0)
                up[i].first = 1 + up[i-1].first;
            else
                up[i].first = up[i-1].first;
            up[i].second = -1 * (nums[i] - nums[i-1]);
        } else if (nums[i] > nums[i-1]) {
            if (up[i-1].second < 0)
                up[i].first = up[i-1].first;
            else
                up[i].first = 1 + up[i-1].first;
            up[i].second = -1 * (nums[i] - nums[i-1]);
        } else
            up[i] = {1, 0};

        up_max = max(up_max, up[i].first);
    }
    
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] < nums[i-1]) {
            if (down[i-1].second <= 0)
                down[i].first = 1 + down[i-1].first;
            else
                down[i].first = down[i-1].first;
            down[i].second = -1 * (nums[i] - nums[i-1]);
        } else if (nums[i] > nums[i-1]) {
            if (down[i-1].second < 0)
                down[i].first = down[i-1].first;
            else
                down[i].first = 1 + down[i-1].first;
            down[i].second = -1 * (nums[i] - nums[i-1]);
        } else
            down[i] = {1, 0};

        down_max = max(down_max, down[i].first);
    }
    return max(up_max, down_max);
}

int main() {
    vector<int> nums = {9, 4, 2, 10, 7, 8, 8, 1, 9};
    cout << LogestTurbulence(nums) << endl;
}
