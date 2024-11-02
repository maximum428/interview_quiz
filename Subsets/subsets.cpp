#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> helper(std::vector<int> &nums, int k) {
  std::vector<int> sub_v;
  int index = 0;
  for (int i = k; i > 0; i >>= 1) {
    if ((i & 1) == 1) {
      sub_v.push_back(nums[index]);
    }
    index++;
  }
  return sub_v;
}

std::vector<std::vector<int>> subsets(std::vector<int> &nums) {
  std::vector<std::vector<int>> res;
  std::sort(nums.begin(), nums.end());
  int max = 1 << nums.size();
  for (int i = 0; i < max; i++) {
    std::vector<int> vec = helper(nums, i);
    res.push_back(vec);
  }
  return res;
}

int main(int argc, char** argv) {
  std::vector<int> nums{1,2, 3};
  auto vecs = subsets(nums);
  
  for (const auto &vec: vecs) {
    std::cout << "[";
    for (const auto &num : vec) {
      std::cout << num << ", ";
    }
    std::cout << "]\n";
  }
}
