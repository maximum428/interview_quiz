#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

int longestConsecutiveSeq3(std::vector<int> &nums) {
    std::unordered_map<int, bool> mp;
    for (int i = 0; i < nums.size(); i++) {
      mp[nums[i]] = true;
    }
    for (int i = 0; i < nums.size(); i++) {
      if (mp.count(nums[i] - 1) >0) {
        mp[nums[i]] = false;
      }
    }
    int maxlen = 0;
    for (int i = 0; i < nums.size(); i++) {
      if (mp[nums[i]] == true) {
        int count = 0; //j = 0, count = 0;
        while (mp.count(nums[i]+count) > 0) {
          //j++;
          count++;
        }
        maxlen = std::max(maxlen, count);
      }
    }
    return maxlen;
}

int longestConsecutiveSeq4(std::vector<int> &nums) {
  std::unordered_set<int> st;
  for (int num: nums) {
    st.insert(num);
  }
  int res = 0;
  for (int num: nums) {
    if (st.find(num-1) == st.end()) {
      int currNum = num;
      int currLength = 1;
      while (st.find(currNum+1) != st.end()) {
        currNum++;
        currLength++;
      }
      res = std::max(res, currLength);
    }
  }
  return res;
}

int main() {
    std::vector<int> nums{100, 4, 200, 1, 3, 2};
    std::cout << longestConsecutiveSeq4(nums) << std::endl;

    return 0;
}
