#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void backtrack(vector<int>& nums, vector<vector<int>>& res, vector<int>& vec, int target, int value, int start) {
  if (vec.size() == 4 && value == target) {
    res.push_back(vec);
    return;
  }

  for (int i = start; i < nums.size(); i++) {
    if (i > start && nums[i] == nums[i-1]) continue;
    vec.push_back(nums[i]);
    backtrack(nums, res, vec, target, nums[i]+value, i+1);
    vec.pop_back();
  }
}

vector<vector<int>> fourSum2(vector<int>& nums, int target) {
  vector<vector<int>> res;
  vector<int> vec;
  sort(nums.begin(), nums.end());
  backtrack(nums, res, vec, target, 0, 0);
  return res;
}

vector<vector<int>> fourSum1(vector<int>& nums, int target) {
  vector<vector<int>> res;
  if (nums.size() < 4) return res;

  sort(nums.begin(), nums.end());

  for (int i = 0; i < nums.size() - 3; i++) {
    if (i > 0 && nums[i] == nums[i-1]) continue;
    for (int j = i+1; j < nums.size() - 2; j++) {
      if (j > i+1 && nums[j] == nums[j-1]) continue;
      int third = j + 1, four = nums.size() - 1;
      while (third < four) {
        int sum = nums[i] + nums[j] + nums[third] + nums[four];
        if (sum < target) {
          third++;
        } else if (sum > target) {
          four--;
        } else {
          vector<int> vec = {nums[i], nums[j], nums[third], nums[four]};
          res.push_back(vec);
          while (third < four && nums[third] == vec[2]) third++;
          while (third < four && nums[four] == vec[3]) four--;
        }
      }
    }
  }
  return res;
}

void printResult(vector<vector<int>>& vecs) {
  for (const auto& vec : vecs) {
    cout << "[";
    for (const auto& num : vec) {
      cout << num << " ";
    }
    cout << "]\n";
  }
}

int main(int argc, char** argv) {
  vector<int> nums = {1, 0, -1, 0, -2, 2};
  int target = 0;
  
  auto res1 = fourSum1(nums, target);
  printResult(res1);

  auto res2 = fourSum2(nums, target);
  printResult(res2);

  return 0;
}
