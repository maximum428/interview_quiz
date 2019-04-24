#include <iostream>

using namespace std;

int countPrimes(int n) {
    if (n <= 1)
        return 0;
    
    int res = 0;
    vector<bool> prime(n, true);
    for (int i = 2; i < n; i++) {
        if (prime[i]) {
            ++res;
            for (int j = 2; i * j < n; j++) {
                prime[i * j] = false;
            }
        }
    }
    return res;
}

bool isPrime(int n) {
    if (n <= 1)
        return false;
    
    for (int i = 2; i < n; i++) {
            if (n % i == 0)
                return false;
    }
    return true;
}

int main() {
    int n = 13;
    cout << "Is prime number? " << isPrime(n) << endl;
    cout << "How many prime number in " << n << ": " << countPrimes(n) << endl;
}
