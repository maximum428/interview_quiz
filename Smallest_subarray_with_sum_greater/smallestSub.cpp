#include <iostream>

using namespace std;

int smallestSubarray(vector<int> vec, int x) {
    int len = vec.size();
    int curr_sum = 0, min_len = len + 1, start = 0, end = 0;
    while (end < len) {
        while (curr_sum <= x && end < len) {
            curr_sum += vec[end++];
        }
        
        while (curr_sum > x && start < len) {
            min_len = min(min_len, end - start);
            /*if (end - start < min_len) {
                min_len = end - start;
            } */
            
            curr_sum -= vec[start++];
        }
    }
    return min_len;
}

int main() {
    vector<int> vec = { 1, 4, 45, 6, 10, 19 };
    cout << smallestSubarray(vec, 51) << endl;
}

=================================================================
#include <iostream>
#include <vector>

using namespace std;


int smallestSubarrayWithSum(const vector<int>& nums, int x) {
    int n = nums.size(), minLen = INT_MAX, sum = 0, start = 0;
    
    for (int end = 0; end < n; end++) {
        sum += nums[end];
        
        while (sum > x) {
            minLen = min(minLen, end - start + 1);
            sum -= nums[start++];
        }
    }
    return (minLen == INT_MAX) ?  -1 : minLen;
}

int main() {
    vector<int> nums = {1, 4, 45, 6, 0, 19};
    int x = 51;
    
    int res = smallestSubarrayWithSum(nums, x);
    if (res == -1) {
        cout << "Not Possible\n";
    } else {
        cout << res << endl;
    }
    return 0;
}
