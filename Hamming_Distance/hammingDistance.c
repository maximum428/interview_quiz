#include<stdio.h>

int hammingDistance(int x, int y) {
    int dist = 0, n = x ^ y;
    printf("n: %d\n", n);
    
    while (n) {
        ++dist;
        n &= n - 1;
    }
    return dist;
}

int main(void) {    
    printf("%d\n", hammingDistance(1, 4));
    return 0;
}
