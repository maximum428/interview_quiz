#include <iostream>
#include <vector>

using namespace std;

int partition(int *nums, int left, int right) {
    int pivot = nums[left], l = left + 1, r = right;
    while (l <= r) {
        if (nums[l] < pivot && nums[r] > pivot) {
          swap(nums[l++], nums[r--]);
        }
        if (nums[l] >= pivot) l++;
        if (nums[r] <= pivot) r--;
    }
    swap(nums[left], nums[r]);
    return r;
}
int findKthLargest(int *nums, int size, int k) {
    int left = 0, right = size - 1;
    while (true) {
        int pos = partition(nums, left, right);
        if (pos == k - 1) {
          return nums[pos];
        }
        if (pos > k -1) {
            right = pos - 1;
        } else {
            left = pos + 1;
        }
    }
}
int main() {
  int nums[] = {3, 2, 1, 5, 6, 4};
  cout << findKthLargest(nums, sizeof(nums)/sizeof(nums[0]), 2) << endl;
  return 0;
}
