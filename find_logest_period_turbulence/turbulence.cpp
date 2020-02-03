int LogestTurbulence(vector<int>& nums) {
    vector<int> up(nums.size(), 1), down(nums.size(), 1);
    //up[0] = 1;
    //down[0] = 1;
    int res = 0;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] > nums[i - 1]) {
            up[i] = down[i - 1] + 1;
        }
        if (nums[i] < nums[i - 1]) {
            down[i] = up[i - 1] + 1;
        }
        res = max(res, max(up[i], down[i]);
    }
    return res;
}

int main() {
    vector<int> nums = {9, 4, 2, 10, 7, 8, 8, 1, 9};
    cout << LogestTurbulence(nums) << endl;
}
