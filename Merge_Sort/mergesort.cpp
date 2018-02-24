#include <iostream>

class Solution {
public:
    void MergeSort(int *arr, int low, int high) {
        int mid;
        if (low < high) {
            mid = (low + high) / 2;
            MergeSort(arr, low, mid);
            MergeSort(arr, mid+1, high);
            
            Merge(arr, low, mid, high);
        }
    }
private:
    void merge(int* arr, int low, int mid, int high) {
        int i, j, k;
        int n1 = mid - low + 1;
        int n2 = high - mid;
        int L[n1], R[n2];
    
        for (i = 0; i < n1; i++)
            L[i] = arr[low + i];
        for (j = 0; j < n2; j++)
            R[j] = arr[mid + j + 1];
        
        i = 0; j = 0; k = low;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j])
                arr[k++] = L[i++];
            else
                arr[k++] = R[j++];
        }
        
        while (i < n1)
            arr[k++] = L[i++];
    
        while (j < n2)
            arr[k++] = R[j++];
    }
};

int main() {
    Solution solution;
    int arr[6] = {2, 6, 3, 9, 5, 1};
    solution.MergeSort(arr, 0, sizeof(arr)/sizeof(arr[0]));
    
    for (auto i : arr) {
        cout << i << " ";
    }
}
