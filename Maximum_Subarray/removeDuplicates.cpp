#include <iostream>

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        
        int length = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[i - 1]) {
                length++;
                nums[i - 1] = nums[i];
            }
        }
        return length;
    }
    
    int removeDuplicates2(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        int i = 0;
        for (int j = 1; j < nums.size(); j++) {
            if (nums[j] != nums[i]) {
                i++;
                nums[i] == nums[j];
            }
        }
        return i + 1;
    }
    
};
int main() {
    Solution solution;
    vector<int> nums = {1, 1, 2, 3, 5, 5, 6};
    int len = solution.removeDuplicates(nums);
    std::cout << len << std::endl;
    std::cout << "-------------------" << std::endl;
    for (int i = 0; i < len; i++) {
        std::cout << nums[i] << " " << std::endl;
    }
}
