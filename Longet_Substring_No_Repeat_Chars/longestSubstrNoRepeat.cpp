#include <iostream>
#include <map>

int lengthOfLongestSubString(std::string s) {
  std::unordered_map<char, int> mp;
  int maxlen = 0, left = 0;
  for (int i = 0; i < s.length(); i++) {
    if (mp.find(s[i]) == mp.end() || mp[s[i]] < left) {
      maxlen = std::max(maxlen, i - left + 1);
    } else {
      left = mp[s[i]] + 1;
    }
    mp[s[i]] = i;
}
