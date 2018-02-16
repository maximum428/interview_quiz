#include<stdio.h>

uint32_t reverseBits(uint32_t n) {
    uint32_t ret = 0;
    for (int i = 0; i < 32; i++, n >>= 1) {
        ret <<= 1;
        ret |= n & 1;
    }
    return ret;
}

int main(void) {
    int n = 13;
    printf("%d\n", reverseBits(n));
    return 0;
}
