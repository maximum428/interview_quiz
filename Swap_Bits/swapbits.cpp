
int swapBits(unsigned int n, unsigned int p1, unsigned int p2) {
    unsigned int bit1 = (n >> p1) & 1;
    unsigned int bit2 = (n >> p2) & 1;
    unsigned int x = (bit1 ^ bit2);
    
    x = (x << p1) | ( x << p2);
    unsigned int result = n ^ x;
}

int main() {
    int res = swapBits(28, 0, 3);
    cout << res << endl;
    return 0;
}
