bool knows(int a, int b);
class Solution {
public:
    int findCelebrity(int n) {
#if 1
        vector<bool> candidates(n, true);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (candidates[i] && i != j) {
                    if (knows(i, j) || !know(j, i)) {
                        candidates[i] = false;
                        break;
                    } else {
                        candidates[j] = false;
                    }
                }
            }
            if (candidates[i]) return i;
        }
#else
        for (int i = 0, j = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (i != j && (knows(i, j) || !(know(j, i)))
                    break;
            }
            if (j == n) return i;
        }
    }
#endif
    return -1;
};
