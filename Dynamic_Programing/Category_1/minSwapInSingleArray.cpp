#include <iostream>

int minSwapInSingleArray(vector<int> vec) {
    int n = vec.size();
    pair<int, int> arrpos[n];
    for (int i = 0; i < n; i++) {
        arrpos[i].first = vec[i];
        arrpos[i].second = i;
    }
        
    sort(arrpos, arrpos+n);
    vector<bool> visted(n, false);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (visted[i] || arrpos[i].second == i)
            continue;
        int cycle_size = 0;
        int j = i;
        while (!visted[j]) {
            visted[j] = true;
            j = arrpos[j].second;
            cycle_size++;
        }
        
        if (cycle_size > 0)
            ans += (cycle_size - 1);
    }
    return ans;
}

int main() {
    vector<int> vec = { 1, 5, 4, 3, 2};
    cout << minSwapInSingleArray(vec) << endl;
    return 0;
}
