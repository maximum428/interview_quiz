#include <iostream>
#include <vector>

using namespace std;

void Merge(vector<int>& vec, int low, int mid, int high) {
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int L[n1], R[n2];
    
    for (i = 0; i < n1; i++)
        L[i] = vec[low + i];
    for (j = 0; j < n2; j++)
        R[j] = vec[mid + j + 1];
    
    i = 0; j = 0; k = low;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            vec[k++] = L[i++];
        else
            vec[k++] = R[j++];
    }
    
    while (i < n1)
        vec[k++] = L[i++];
    
    while (j < n2)
        vec[k++] = R[j++];
}

void MergeSort(vector<int>& vec, int low, int high) {
    int mid;
    if (low < high) {
        mid = low + (high - low) / 2;  // (low + high) / 2;
        MergeSort(vec, low, mid);
        MergeSort(vec, mid+1, high);
        
        Merge(vec, low, mid, high);
    }
}

int main() {
    vector<int> vec = { 9, 5, 2, 3, 1, 8 };
    MergeSort(vec, 0, vec.size() - 1);
    
    for (auto v : vec) {
        cout << v << " ";
    }
}
