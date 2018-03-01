class Solution {
public:
    void merge1(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n - 1, k = m + n - 1;
        nums1.resize(m+n);
        while (j >= 0) {
            nums1[k--] = i >= 0 && nums1[i] >= nums2[j] ? nums1[i--] : nums2[j--];
        }
    }
    
    void merge2(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n - 1, k = m + n - 1;
        nums1.resize(m+n);
        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else if (nums1[i] < nums2[j]) {
                nums1[k--] = nums2[j--];
            } 
        }
        while (i >= 0) {
            nums1[k--] = nums1[i--];
        }
        while (j >= 0)
            nums1[k--] = nums2[j--];
    }
};

int main() {
    Solution solution;
    vector<int> vec1 = {1, 3, 8, 10}, vec2 = {2, 6, 8, 9};
    solution.merge2(vec1, vec1.size(), vec2, vec2.size());
    for (auto v : vec1) {
        cout << v << " ";
    }
}
