#include <iostream>
#include <vector>

using namespace std;

void InsertionSort(vector<int>& vec) {
    if (vec.size() < 2)
        return;
    
    for (int unsorted = 1;  unsorted < vec.size(); unsorted++) {
        int hold = vec[unsorted];
        int i = unsorted - 1;
        while (i >= 0 && hold < vec[i]) {
            vec[i+1] = vec[i];
            i -= 1;
        }
        vec[i+1] = hold;
        print(vec);
    }
}

int main() {
    vector<int> vec = { 9, 5, 2, 3, 1, 8 };
    InsertionSort(vec);
    
    for (auto v : vec) {
        cout << v << " ";
    }
}
