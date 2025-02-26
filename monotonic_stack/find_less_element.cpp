#include <vector>
#include <stack>
#include <iostream>

using namespace std;

// Find the previous less element of each element in a vector with O(n) time
vector<int> findPrevLess(vector<int> nums) {
  vector<int> previous_less(nums.size(), -1);
  stack<int> in_stk;

  for (int i = 0; i < nums.size(); i++) {
    while (!in_stk.empty() && nums[in_stk.top()] > nums[i]) {
      in_stk.pop();
    }
    previous_less[i] = in_stk.empty() ? -1 : in_stk.top();
    in_stk.push(i);
  }
  return previous_less;
}

// Find the next less element of each element in a vector with O(n) time
vector<int> findNextLess(vector<int> nums) {
  vector<int> next_less(nums.size(), -1);
  stack<int> in_stk;

  for (int i = 0; i < nums.size(); i++) {
    while (!in_stk.empty() && nums[in_stk.top()] > nums[i]) {
      auto x = in_stk.top();
      in_stk.pop();
      next_less[x] = i;
    }
    in_stk.push(i);
  }
  return next_less;
}

// Find the previous large element of each element in a vector with O(n) time
vector<int> findPrevLarge(vector<int> nums) {
  vector<int> previous_large(nums.size(), -1);
  stack<int> in_stk;

  for (int i = 0; i < nums.size(); i++) {
    while (!in_stk.empty() && nums[in_stk.top()] < nums[i]) {
      in_stk.pop();
    }
    previous_large[i] = in_stk.empty() ? -1 : in_stk.top();
    in_stk.push(i);
  }
  return previous_large;
}

// Find the next large element of each element in a vector with O(n) time
vector<int> findNextLarge(vector<int> nums) {
  vector<int> next_large(nums.size(), -1);
  stack<int> in_stk;

  for (int i = 0; i < nums.size(); i++) {
    while (!in_stk.empty() && nums[in_stk.top()] < nums[i]) {
      auto x = in_stk.top();
      in_stk.pop();
      next_large[x] = i;
    }
    in_stk.push(i);
  }
  return next_large;
}

void printList(vector<int>& nums) {
  for (const int& num : nums) {
    cout << num << ", ";
  }
  cout << "\n";
}
int main(int argc, char** argv) {
  vector<int> nums = {73, 74, 75, 71, 69, 72, 76, 73};
                      //1,  2,  6,  5,  5,  6,  -1, -1
                      //-1, -1, -1, 2,  3,  2,  -1, 6

  auto list = findPrevLarge(nums);

  printList(list);

  return 0;
}
