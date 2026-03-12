/* Given a 32 bit number, return the number of intervals which bits are 1. 
For example: 001100111011 returns 3 intervals of bits which have 1. */

#include <bit>
#include <iostream>

using namespace std;

int couuntIntervals2(uint32_t x) {
  int count = 0, prev = 0;

  for (int i = 0; i < 32; i++) {
    int bit = (x >> i) & 1;
    if (bit == 1 && prev == 0) {
      count++;
    }
    prev = bit;
  }
  return count;
}

int countIntervals(uint32_t x) {
  uint32_t starts = x & ~(x >> 1);
  return __builtin_popcount(starts);
}

/********************************
  x           = 001100111011
  x >> 1      = 000110011101
~(x >> 1)     = 111001100010
-------------------------------
x & ~(x >> 1) = 001000100010
**********************************/
int main() {
  uint32_t x = 001100111011;
  cout << countIntervals(x) << endls;
  return 0;
}

/* follow-up:   Give a 128 bit integer. */
struct Uint128 {
  uint64_t hi;
  uint32_t lo;
};

/********************
  這裡最重要的是什麼？

最重要的是：

prev

不能在掃完 lo 後重設。

因為如果：

lo 的最高 bit 是 1

hi 的最低 bit 也是 1

那它們其實是同一段連續的 1
***************************/
int countIntervals(const Uint128& x) {
  int count = 0, prev = 0;

  for (int i = 0; i < 64; ++i) {
    int bit = (x.lo >> i) & 1ULL;
    if (bit == 1 && prev == 0) {
      count++;
    }
    prev = bit;
  }

  for (int i = 0; i < 64; i++) {
    int bit = (x.hi >> i) & 1ULL;
    if (bit == 1 && prev == 0) {
      count++;
    }
    prev = bit;
  }
  return count;
}

int countIntervals64(uint64_t x) {
  uint64_t starts = x & ~(x >> 1);
  return __builtin_popcountll(starts);
}
int countIntervals2(const Uint128& x) {
  int count = countIntervals64(x.lo) + countIntervals64(x.hi);

  // 檢查跨 64-bit 邊界是否其實是同一段
  int lo_msb = (x.lo >> 63) & 1ULL;
  int hi_lsb = x.hi & 1ULL;
  if (lo_msb == 1 && hi_lsb == 1) {
    count--;  // 原本被算成兩段，其實是一段
  }
  return count;
}

/*
  int32_t x[4];
*/
int countIntervals(const int32_t *x) {
  int count = 0, prev = 0;
  for (int i = 0; i < 128; i++) {
    int word = x[i / 32];
    int bit = (word >> (i % 32)) & 1;

    if (bit == 1 && prev == 0) {
      count++;
    }
    prev = bit;
  }
  return count;
}

int countIntervals2(const int32_t *x) {
  int count = 0, prev = 0;

  for (int w = 0; w < 4; w++) {
    uint32_t x = x[w];

    for (int b = 0; b < 32; b++) {
      int bit = (x >> b) & 1;

      if (bit == 1 && prev == 0) {
        count++;
      }
      prev = bit;
    }
  }
  return count;
}
