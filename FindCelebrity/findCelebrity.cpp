bool knows(int a, int b);
class Solution {
public:
    int findCelebrity(int n) {
        for (int i = 0, j = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (i != j && (knows(i, j) || !(know(j, i)))
                    break;
            }
            if (j == n) return i;
        }
    }
    return -1;
};
