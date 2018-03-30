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

//O(nlogn)
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

//O(n^2)
int longestIncresingSubseq(vector<int> nums) {
    if (nums.size() == 0) return 0;
    vector<int> f(nums.size(), 1);
    
    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j])
                f[i] = max(f[i], f[j] + 1);
        }
    }
    return *max_element(f.begin(), f.end());
}

vector<int> f_;

int LIS(const vector<int>& nums, int r) {
    if (r == 0) return 1;
    if (f_[r] > 0) return f_[r];
    int ans = 1;
    for (int i = 0; i < r; i++)
        if (nums[r] > nums[i])
            ans = max(ans, LIS(nums, i) + 1);
    f_[r] = ans;
    return f_[r];
}

int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    f_ = vector<int>(n, 0);
    int ans = 0;
    for (int i = 0; i < n; ++i) 
        ans = max(ans, LIS(nums, i));
    return ans;
}

//O(nlogn)
int lengthOfLIS2(vector<int>& nums) {
    vector<int> tails(nums.size(), 0);
    int res = 0;
    for (auto num : nums) {
        int i = 0, j = res;
        while (i != j) {
            int mid = (i + j) / 2;
            if (tails[mid] < num) {
                i = mid + 1;
            } else {
                j = mid;
            }
        }
        tails[i] = num;
        if (i == res) ++res;
    }
    return res;
}
int main() {
    vector<int> vec = { 5, 2, 6, 3, 4, 7, 5};
    cout << lengthOfLIS(vec) << endl;
    cout << longestIncresingSubseq(vec) << endl;
    cout << longestAscendingSubsequence(vec) << endl;
}
