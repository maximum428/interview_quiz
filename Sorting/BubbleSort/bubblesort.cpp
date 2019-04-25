#include <iostream>
#include <vector>

using namespace std;

void BubbleSort(vector<int>& vec) {
    if (vec.size() == 0)
        return;
    
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec.size(); j++) {
            if (vec[i] < vec[j]) {
                vec[i] = vec[i] ^ vec[j];
                vec[j] = vec[i] ^ vec[j];
                vec[i] = vec[i] ^ vec[j];
            }
        }
    }
}

int main() {
    vector<int> vec = { 9, 5, 2, 3, 1, 8 };
    BubbleSort(vec);
    
    for (auto v : vec) {
        cout << v << " ";
    }
}
