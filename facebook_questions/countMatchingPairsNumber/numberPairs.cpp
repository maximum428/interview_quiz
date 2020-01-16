#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the numberPairs function below.
int numberPairs(int n, vector<int> ar) {
    unordered_map<int, int> mp;
    int res = 0;

    for (int i = 0; i < n; i++) {
        mp[ar[i]]++;
    }

    for (auto n : mp) {
        res += (n.second/2);
    }
    return res;
}
