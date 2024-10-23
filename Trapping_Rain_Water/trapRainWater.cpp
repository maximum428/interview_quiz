#include <iostream>
#include <vector>

int TrapRainWater(std::vector<int> &nums) {
    int left = 0, right = nums.size() - 1, res = 0;
    
    while (left < right) {
        int low = std::min(nums[left], nums[right]);
        if (low == nums[left]) {
            left++;
            while (left < right && low > nums[left]) {
                res += low - nums[left++];
            }
        } else {
            right--;
            while (left < right && low > nums[right]) {
                res += low -nums[right--];
            }
        }
    }
    return res;
}

int TrapRainWater2(int *nums, int len) {
    int left = 0, right = len - 1, res = 0;
    while (left < right) {
        int low = std::min(nums[left], nums[right]);
        if (low == nums[left]) {
            left++;
            while (left < right && low > nums[left]) {
                res += low - nums[left++];
            }
        } else {
            right--;
            while (left < right && low > nums[right]) {
                res += low - nums[right--];
            }
        }
    }
    return res;
}
int main() {
    std::vector<int> nums = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int nums2[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int length = sizeof(nums2)/sizeof(nums2[0]);
    std::cout << TrapRainWater2(nums2, length) << std::endl;
    
    return 0;
}
