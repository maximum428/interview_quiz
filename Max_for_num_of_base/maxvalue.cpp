#include <iostream>

using namespace std;

int MaxValue(int base, int n) {
    int max = base;
    for (int i = 1; i < n; i++) {
        max *= base;
    }
    return max - 1;
}

int MaxValue2(int base, int n) {
    if (n == 1)
        return base;
    
    base = base * base;
    return MaxValue2(base, n - 1) - 1;
}
int main() {
    int base = 2, n = 4;
    
    int max = MaxValue2(base, n-1);
    cout << max << endl;
}
