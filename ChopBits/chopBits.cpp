/* Given a number, get the bits on given position and length.
For example:   n = 01101001, pos = 3, len = 4,
               return 1101
*/

uint32_t chopBits(uint32_t n, uint32_t pos, uint32_t len) {
    return (((1 << len) - 1) & (n >> (pos - 1)));
    /*
    int32_t mask = -1;    // -1 = 11111....11111;
    mask = ~(mask << len);  // same as mask <<= len; mask = ~mask;
    n >>= pos;
    return n & mask; */
}
