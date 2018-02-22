#include <iostream>

class Solution{
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int len = nums.size();
        for (int i = 0; i < len; i++) {
            int m = abs(nums[i]) - 1;
            nums[m] = nums[m] > 0 ? -nums[m] : nums[m];
        }
        
        vector<int> res;
        for (int i = 0; i < len; i++) {
            if (nums[i] > 0) {
                res.push_back(i+1);
            }
        }
        return res;
    }
};

int main() {
    Solution solution;
    vector<int> vec = {4, 3, 2, 7, 800, 2, 3, 1};
    vector<int> ret = solution.findDisappearedNumbers(vec);
    for (auto e : ret) {
        cout << e << endl;
    }
}
