// find the index of largest number in m which is smaller than target
int findLargest(vector<int>& m, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (m[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return right;
}
int longestAscendingSubsequence(vector<int> nums) {
    if (nums.size() == 0) return 0;
    // m[] 數組紀錄到目前為止最優的最長升序列
    vector<int> m(nums.size(), 0);
    m[0] = nums[0];  // 最少第一個元素本身就是長度為的最長子序列
    int result = 1;
    for (int i = 1; i < nums.size(); i++) {
        // 注意是在m數組裡要找出 nums[i] 小的最大數的index
        int largestSmallerThanTargetIndex = findLargest(m, 0, result - 1, nums[i]);
        // result - 1 是長度為result的數組最後一個元素的index
        if (largestSmallerThanTargetIndex == result - 1) {
            // nums[i] 比 m 裡所有數都大，此時要在 m 最後加一個元素
            m[result] = nums[i];
            result++;
        } else {
            // 把第一個大於nums[i]的數換成nums[i]
            m[largestSmallerThanTargetIndex + 1] = nums[i];
        }
    }
    return result;
}

int main() {
    vector<int> vec = { 5, 2, 6, 3, 4, 7, 5};
    cout << longestAscendingSubsequence(vec) << endl;
}
