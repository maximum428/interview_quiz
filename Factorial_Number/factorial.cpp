#include <iostream>

using namespace std;

int factorial(int n) {
    if (n < 2)
        return 1;
    
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int factorial2(int n) {
    if (n < 2)
        return 1;
    
    return factorial2(n - 1) * n;
}

int main() {
    int n = 6;
    cout << factorial2(n) << endl;
}
