#include <iostream>

int SumOfArithmeticSeries(int x, int d, int y) {
    return (x + x + d * (y - 1)) * y/2;
}
int main() {
    int n = 9;
   
    int sum_3 = SumOfArithmeticSeries(3, 3, n/3);
    int sum_5 = SumOfArithmeticSeries(5, 5, n/5);
    int sum_15 = SumOfArithmeticSeries(15, 15, n/15);
    std::cout << (sum_3+sum_5-sum_15) << std::endl;
}
