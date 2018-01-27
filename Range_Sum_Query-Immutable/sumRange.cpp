#include <iostream>

class NumArray {
public:
    NumArray(vector<int> nums) {
        this->_nums = nums;
        
        _sum = {0};
        for (int i = 0; i < nums.size(); i++) {
            _sum.push_back(_sum[i] + nums[i]);
        }
    }
    
    int sumRange1(int i, int j) {
        if (_nums.size() == 0) return 0;
        if (i < 0 || j < 0) throw invalid_argument("Error: Incorrect input.");
        
        int sum = 0;
        for (int start = i, x = 0; x < j - i + 1; start++, x++) {
            sum += _nums[start];
        }
        return sum;
    }
    
    int sumRange2(int i, int j) {
        int sum = 0;
        for (int k = i; k <= j; k++) {
            sum += _nums[k];
        }
        return sum;
    }
    
    int sumRange3(int i, int j) {
        return _sum[j + 1] - _sum[i];
    }
    
private:
    vector<int> _nums;
    vector<int> _sum;
};

int main() {
    vector<int> nums{-2, 0, 3, -5, 2, -1};
    
    NumArray obj(nums);
    std::cout << obj.sumRange3(2, 5) << std::endl;
}
