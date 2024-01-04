#include <iostream>
#include <math.h>
using namespace std;

unsigned int getFirstSetBitPos(int n) {
    int i = (n & ~(n-1));
    cout << i << endl;
    
    return log2(i) + 1;
}

unsigned int getFirstSetBitPos2(int n) {
    int i = (n & -n);
    cout << i << endl;
    return log2(i) + 1;
}

unsigned int getFirstSetBitPos3(int n) {
    if (n == 0) return 0;

    int pos = 1, m = 1;
    while (!(n & m)) {
        pos++;
        m <<= 1;
    }
    return pos;
}

#define INT_SIZE 32

unsigned int getFirstSetBitPos4(int n) {
    if (n == 0) {
        return 0;
    } else {
        int pos = 1;
        for (int i = 0; i < INT_SIZE; i++) {
            if (n & (1 << i)) {
                break;
            } else {
                pos++;
            }
        }
        return pos;
    }
}

unsigned int getFirstSetBitPos5(int n) {
    int pos = 1;

    while (n > 0) {
        if (n & 1) {
            return pos;
        }
        pos++;
        n >>= 1;
    }
    return 0;
}

int main() {
    cout << getFirstSetBitPos5(12) << endl;
    return 0;
}
