class Solution {
public:
    int reverse(int x) {
        long long res = 0;
        while(x) {
            res = res*10 + x%10;
            x /= 10;
        }
        return (res<INT_MIN || res>INT_MAX) ? 0 : res;
    }
    int reverse2(int x) {
        int result = 0;
        while (x) {
            int tail = x % 10;
            int tmp = result * 10 + tail;
            if ((tmp - tail) / 10 != result)
                return 0;
            result = tmp;
            x /= 10;
        }
        return result;
    }
};
