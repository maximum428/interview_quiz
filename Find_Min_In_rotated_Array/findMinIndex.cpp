#include <iostream>

using namespace std;

int findMin(int arr[], int low, int high){
    if (high < low) return arr[0];
    if (high == low) return arr[low];
    
    int mid = low + (high - low) / 2;
    
    if (mid < high && arr[mid + 1] < arr[mid])
        return arr[mid + 1];
    if (mid > low && arr[mid] < arr[mid - 1])
        return arr[mid];
    if (arr[high] > arr[mid])
        return findMin(arr, low, mid - 1);
    return findMin(arr, mid + 1, high);
}

int findMinIndex(int arr[], int low, int high){
    if (high < low) return 0;
    if (high == low) return low;
    
    int mid = low + (high - low) / 2;
    
    if (mid < high && arr[mid + 1] < arr[mid])
        return mid + 1;
    if (mid > low && arr[mid] < arr[mid - 1])
        return mid;
    if (arr[high] > arr[mid])
        return findMinIndex(arr, low, mid - 1);
    return findMinIndex(arr, mid + 1, high);
}

int main(){
    int arr1[] = {5, 6, 1, 2, 3, 4};  
    int n1 = sizeof(arr1)/sizeof(arr1[0]);  
    cout << "The index of minimum element is " << findMinIndex(arr1, 0, n1-1) << endl;
    
    int arr2[] = {1, 2, 3, 4};  
    int n2 = sizeof(arr2)/sizeof(arr2[0]);  
    cout << "The index of minimum element is " << findMinIndex(arr2, 0, n2-1) << endl;
    
    int arr3[] = {1};  
    int n3 = sizeof(arr3)/sizeof(arr3[0]);  
    cout<<"The index of minimum element is "<<findMinIndex(arr3, 0, n3-1)<<endl;
    
    int arr4[] = {1, 2};  
    int n4 = sizeof(arr4)/sizeof(arr4[0]);  
    cout<<"The index of minimum element is "<<findMinIndex(arr4, 0, n4-1)<<endl;  
  
    int arr5[] = {2, 1};  
    int n5 = sizeof(arr5)/sizeof(arr5[0]);  
    cout<<"The index of minimum element is "<<findMinIndex(arr5, 0, n5-1)<<endl;  
  
    int arr6[] = {5, 6, 7, 1, 2, 3, 4};  
    int n6 = sizeof(arr6)/sizeof(arr6[0]);  
    cout<<"The index of minimum element is "<<findMinIndex(arr6, 0, n6-1)<<endl;  
  
    int arr7[] = {1, 2, 3, 4, 5, 6, 7};  
    int n7 = sizeof(arr7)/sizeof(arr7[0]);  
    cout << "The index of minimum element is " << findMinIndex(arr7, 0, n7-1) << endl;  
  
    int arr8[] = {2, 3, 4, 5, 6, 7, 8, 1};  
    int n8 = sizeof(arr8)/sizeof(arr8[0]);  
    cout << "The index of minimum element is " << findMinIndex(arr8, 0, n8-1) << endl;  
  
    int arr9[] = {3, 4, 5, 1, 2};  
    int n9 = sizeof(arr9)/sizeof(arr9[0]);  
    cout << "The index of minimum element is " << findMinIndex(arr9, 0, n9-1) << endl;
    return 0;
}
