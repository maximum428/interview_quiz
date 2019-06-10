int minSwap(vector<int> &A, vector<int> &B) {
    int n = A.size();
    vector<int> keep(n, INT_MAX);
    vector<int> swap(n, INT_MAX);
    
    keep[0] = 0;
    swap[0] = 1;
    
    for (int i = 1; i < n; i++) {
        if (A[i] > A[i - 1] && B[i] > B[i - 1]) {
            keep[i] = keep[i -1];
            swap[i] = swap[i - 1] + 1;
        }
        if (B[i] > A[i - 1] && A[i] > B[i - 1]) {
            swap[i] = min(swap[i], keep[i - 1] + 1);
            keep[i] = min(keep[i], swap[i - 1]);
        }
    }
    return min(keep.back(), swap.back());
}

int main() {
    vector<int> A = { 1, 3, 5, 4}, B = {1, 2, 3, 7};
    cout << minSwap(A, B) << endl;
}
