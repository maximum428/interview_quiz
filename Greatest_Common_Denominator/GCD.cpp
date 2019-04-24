#include <iostream>

using namespace std;

int GreatestCommonDenominator(int m, int n) {
    if (n == 0) {
        return m;
    }
    return GreatestCommonDenominator(n, m % n);
}

int main() {
    int m = 9, n = 15;
    cout << "Greatest common denominator of " << m << " and " << n << " is ";
    cout << GreatestCommonDenominator(m, n) << endl;
}
