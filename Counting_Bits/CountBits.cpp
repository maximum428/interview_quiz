#include <iostream>
/*
这道题给我们一个整数n，然我们统计从0到n每个数的二进制写法的1的个数，存入一个一维数组中返回，题目中明确表示不希望我们一个数字一个数字，一位一位的傻算，而是希望我们找出规律，而且题目中也提示了我们注意[2-3], [4-7], [8-15]这些区间的规律，那么我们写出0到15的数的二进制和1的个数如下：
0    0000    0
-------------
1    0001    1
-------------
2    0010    1
3    0011    2
-------------
4    0100    1
5    0101    2
6    0110    2
7    0111    3
-------------
8    1000    1
9    1001    2
10   1010    2
11   1011    3
12   1100    2
13   1101    3
14   1110    3
15   1111    4
*/
class Solution {
public:
    vector<int> CountBits1(int num) {
        if (num == 0) return {0};
        vector<int> bits{0, 1};
        int k = 2, i = 2;
        while (i <= num) {
            for (i = pow(2, k - 1); i < pow(2, k); ++i) {
                if (i > num) break;
                int t = (pow(2, k) - pow(2, k - 1)) / 2;
                if (i < pow(2, k - 1) + t) bits.push_back(bits[i - t]);
                else bits.push_back(bits[i - t] + 1);
            }
            ++k;
        }
        return bits;
    }
    /*
    解法二：
    下面来看一种投机取巧的方法，直接利用了built-in的函数bitset的count函数可以直接返回1的个数，题目中说了不提倡用这种方法，写出来只是多一种思路而已
    */
    vector<int> CountBits2(int num) {
        vector<int> bits;
        for (int i = 0; i <= num; ++i) {
            bits.push_back(bitset<32>(i).count());
        }
        return bits;
    }
    /*
    解法三：
    下面这种方法相比第一种方法就要简洁很多了，这个规律找的更好，规律是，从1开始，遇到偶数时，其1的个数和该偶数除以2得到的数字的1的个数相同，遇到奇数时，其1的个数等于该奇数除以2得到的数字的1的个数再加1
    */
    vector<int> CountBits3(int num) {
        vector<int> bits{0};
        for (int i = 1; i <= num; i++) {
            if (i % 2 == 0) bits.push_back(bits[i / 2]);
            else bits.push_back(bits[i / 2] + 1);
        }
        return bits;
    }
    
    /*
    解法四：
下面这种方法就更加巧妙了，巧妙的利用了i&(i - 1)， 这个本来是用来判断一个数是否是2的指数的快捷方法，比如8，二进制位1000, 那么8&(8-1)为0，只要为0就是2的指数, 那么我们现在来看一下0到15的数字和其对应的i&(i - 1)值：

复制代码
i    bin       '1'    i&(i-1)
0    0000    0
-----------------------
1    0001    1    0000
-----------------------
2    0010    1    0000
3    0011    2    0010
-----------------------
4    0100    1    0000
5    0101    2    0100
6    0110    2    0100
7    0111    3    0110
-----------------------
8    1000    1    0000
9    1001    2    1000
10   1010    2    1000
11   1011    3    1010
12   1100    2    1000
13   1101    3    1100
14   1110    3    1100
15   1111    4    1110
复制代码
我们可以发现每个i值都是i&(i-1)对应的值加1
    */
    vector<int> CountBits4(int num) {
        vector<int> bits(num + 1, 0);
        for (int i = 1; i <= num; ++i) {
            bits[i] = bits[i & (i - 1)] + 1;
        }
        return bits;
    }
};

int main() {
    int n = 5;
    Solution solution;
    for (auto i : solution.CountBits4(5))
        std::cout << i << " ";
}
