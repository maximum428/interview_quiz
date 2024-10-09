/*
For example: Given string array of {"10", "2", "2", "3", "#", "#", "3"} representing 
Tree List of:
       10
      /  \
     2    2
    / \  / \
   3  # #   3

Check if the string arrary is symetric tree list structure.
*/


#include <iostream>

bool IsPalindrone(std::string *arr, int pos, int length) {
    int left = pos, right = pos + length - 1;
    //std::cout << "left: " << left << ";  right: " << right << std::endl;
    for (auto left = pos, right = pos + length - 1; left <= right; left++, right--) {
        if (*(arr+left) != *(arr+right)) {
            return false;
        }
        //std::cout << *(arr+left) << " -- " << *(arr+right) << std::endl;
    }
    return true;
}
bool IsSymmetric(std::string *arr, int length) {
    if ((length % 2) == 0) return false;
    
    for (int pos = 1, len = 2; pos+len <= length; pos+=len, len*=2) {
        //std::cout << "pos: " << pos << "; len: " << len << std::endl;
        if (!IsPalindrone(arr, pos, len)) {
            return false;
        }
    }
    return true;
}

int main() {
    std::string nums[] = {"10", "2", "2", "3", "#", "#", "3"};
    
    int length = sizeof(nums) / sizeof(nums[0]);
    std::cout << length << std::endl;
    
    std::cout << *(nums + 3) << std::endl;
    std::cout << "Is symmetric: " << (IsSymmetric(nums, length) ? "True" : "False") << std::endl;
    
    return 0;
}
