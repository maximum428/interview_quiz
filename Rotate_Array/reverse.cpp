#include <iostream>
/*
Input: TreeNode, sum
Output: boolean
*/
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int temp, previous;
        for (int i = 0; i < k; i++) {
            previous = nums[nums.size() - 1];
            cout << "previous: " << previous << endl;
            for (int j = 0; j < nums.size(); j++) {
                cout <<"nums[j]: " << nums[j] << endl;
                temp = nums[j];
                nums[j] = previous;
                previous = temp;
            }
        }
        for (auto n :nums)
            cout << n << " ";
    }
    
    void rotate4(vector<int>& nums, int k) {
        if (nums.size() == 0) return;
        k = k % nums.size();
    
        while (k--) {
            int pre = nums[0];
            for (int i = 1; i < nums.size(); i++) {
                int tmp = nums[i];
                nums[i] = pre;
                pre = tmp;
            }
            nums[0] = pre;
        }
    }
    
    void rotate1(vector<int>& nums, int k) {
        vector<int> vec(nums.size(), 0);
        for (int i = 0; i < nums.size(); i++) {
            cout << "i: " << i << "; (i + k): " << (i + k) << "; (i + k ) % nums.size(): " << ((i+k)%nums.size()) << endl;
            vec[(i + k) % nums.size()] = nums[i];
        }
        for (auto v : vec)
            cout << v << " ";
    }
    
    void rotate2(vector<int>& nums, int k) {
        k = k % nums.size();
        cout << "k: " << k << endl;
        int count = 0;
        for (int start = 0; count < nums.size(); start++) {
            int current = start;
            int prev = nums[start];
            cout << "current: " << current << "; prev: " << prev << endl;
            do {
                int next = (current + k) % nums.size();
                cout << "count: " << count << "; next: " << next << "; nms[next]: " << nums[next] << endl;
                int temp = nums[next];
                nums[next] = prev;
                prev = temp;
                current = next;
                count++;
            } while (start != current);
        }
        for (auto n :nums)
            cout << n << " ";
    }
    
    void rotate3(vector<int>& nums, int k) {
        k %= nums.size();
#if 1
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin()+k);
        reverse(nums.begin()+k, nums.end());
#else        
        reverse(nums, 0, nums.size() - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, nums.size() - 1);
#endif
        for (auto n : nums)
            cout << n << " ";
    }
private:
    void reverse(vector<int>& nums, int start, int end) {
        while (start < end) {
            int tmp = nums[start];
            nums[start] = nums[end];
            nums[end] = tmp;
            start++;
            end--;
        }
    }
};

int main() {
    Solution solution;
    vector<int> vec1 = {1, 2, 3, 4, 5, 6};
    int k = 11;
    solution.rotate3(vec1, 3);
}
