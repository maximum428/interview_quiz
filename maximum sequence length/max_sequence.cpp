#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int MaxSequence(vector<int>& nums) {
    if (nums.size() < 2) return nums.size();
    
    sort(nums.begin(), nums.end());
    int res = 0, subseq_length = 1;
    
    for (auto i = 0; i < nums.size() - 1; i++) {
        if (nums.at(i) == nums.at(i+1) || nums.at(i) + 1 == nums.at(i+1)) {
            subseq_length++;
        } else {
            res = max(res, subseq_length);
            subseq_length = 1;
        }
    }
    
    return res;
    
}

int main()
{
    std::vector<int> vec = {5, 4, 3, 2, 1, 8, 8, 8, 9};
    cout << "maxmum length: " << MaxSequence(vec) << endl;
    
    return 0;
}
