#include<stdio.h>

uint32_t reverseBits(uint32_t n) {
    uint32_t ret = 0;
    for (int i = 0; i < 32; i++, n >>= 1) {
        ret <<= 1;
        ret |= n & 1;
    }
    return ret;
}
uint32_t reverseBits(uint32_t n) {
   n = (n & 0xFFFF0000) >> 16 | (n & 0x0000FFFF) << 16;
   n = (n & 0xFF00) >> 8 | (n & 0x00FF) << 8;
   n = (n & 0xF0) >> 4 | (n & 0x0F) << 4;
   n = (n & 0xCC) >> 2 | (n & 0x33) << 2;
   n = (n & 0xAA) >> 1 | (n & 0x55) << 1;
}

int main(void) {
    int n = 13;
    printf("%d\n", reverseBits(n));
    return 0;
}
