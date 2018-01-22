#include <iostream>

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++) {
            int complement = target -nums[i];
            if (hash.find(complement) != hash.end()) {
                return vector<int> {hash[complement], i};
            }
            hash[nums[i]] = i;
        }
        throw std::invalid_argument("no two sum solution");
    }
};

int main() {
    Solution solution;
    vector<int> vec = { 2, 3, 4};
    std::cout << "result: " << std::endl;
    for (auto v : solution.twoSum(vec, 6)) {
        std::cout << v << " ";
    }
}
