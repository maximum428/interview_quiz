#include <iostream>

class Solution {
public:
    void MergeSort(int *arr, int low, int high) {
        int mid;
        if (low < high) {
            mid = (low + high) / 2;
            MergeSort(arr, low, mid);
            MergeSort(arr, mid+1, high);
            
            Merge(arr, low, high, mid);
        }
    }
private:
    void Merge(int *arr, int low, int high, int mid) {
        int i, j, k, tmp[high-low+1];
        i = low;
        k = 0;
        j = mid + 1;
        
        while (i <= mid && j <= high) {
            if (arr[i] < arr[j]) {
                tmp[k] = arr[i];
                k++;
                i++;
            } else {
                tmp[k] = arr[j];
                k++;
                j++;
            }
        }
        
        while (i <= mid) {
            tmp[k] = arr[i];
            k++;
            i++;
        }
        while (j <= high) {
            tmp[k] = arr[j];
            k++;
            j++;
        }
        
        for (i = low; i <= high; i++) {
            arr[i] = tmp[i - low];
        }
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
