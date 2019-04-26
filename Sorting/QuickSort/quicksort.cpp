#include <iostream>
#include <vector>

using namespace std;

void quickSort(vector<int>& vec, int left, int right) {
    if (vec.size() < 2)
        return;
    
    int i = left, j = right, tmp;
    int pivot = vec[(left + right) / 2];
    while (i <= j) {
        while (vec[i] < pivot) i++;
        while (vec[j] > pivot) j--;
        
        if (i <= j) {
            tmp = vec[i];
            vec[i] = vec[j];
            vec[j] = tmp;
            i++;
            j--;
        }
    }
    if (left < j) quickSort(vec, left, j);
    if (i < right) quickSort(vec, i, right);
}

int main() {
    vector<int> vec = { 9, 5, 2, 3, 1, 8 };
    quickSort(vec, 0, vec.size() - 1);
    
    for (auto v : vec) {
        cout << v << " ";
    }
}
