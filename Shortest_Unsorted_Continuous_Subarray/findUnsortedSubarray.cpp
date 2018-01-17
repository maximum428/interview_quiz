#include <iostream>

int findUnsortedSubarray(vector<int>& nums) {
        int shortest = 0;
        
        int left = 0, right = nums.size() - 1;
        while (left < nums.size() - 1 && nums[left] <= nums[left + 1]) { left++; }
        while (right > 0 && nums[right] >= nums[right - 1]) { right--; };
        std::cout << "Left: " << left << "; Right: " << right;
        
        if (right > left) {
            int vmin = INT_MAX, vmax = INT_MIN;
            for (int i = left; i <= right; ++i) {
                if (nums[i] > vmax) {
                    vmax = nums[i];
                }
                if (nums[i] < vmin) {
                    vmin = nums[i];
                }
            }
            std::cout << "vmin: " << vmin << "; vmax: " << vmax << std::endl;
            while (left >= 0 && nums[left] > vmin) { left--; };
            while (right < nums.size() && nums[right] < vmax) { right++; };
            std::cout << "left: " << left << "; right: " << right << std::endl;
            shortest = right - left - 1;
        }
        
        return shortest;
    }

int main() {
    vector<int> vec = {2, 6, 4, 8, 10, 9, 15};
    std::cout << findUnsortedSubarray(vec) << std::endl;
}
