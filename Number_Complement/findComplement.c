#include<stdio.h>
/*
Example:
num          = 00000101
mask         = 11111000
~mask & ~num = 00000010
*/
int findComplement(int num) {
    unsigned int mask = ~0;
    while (num & mask) {
        mask <<= 1;
    }
    return ~mask & ~num;
}

int main(void) {
    printf("%d\n", findComplement(5));
    return 0;
}
