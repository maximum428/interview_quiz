#include <iostream>

using namespace std;

int smallestSubarray(vector<int> vec, int x) {
    int len = vec.size();
    int curr_sum = 0, min_len = len + 1, start = 0, end = 0;
    while (end < len) {
        while (curr_sum <= x && end < len) {
            curr_sum += vec[end++];
        }
        
        while (curr_sum > x && start < len) {
            min_len = min(min_len, end - start);
            /*if (end - start < min_len) {
                min_len = end - start;
            } */
            
            curr_sum -= vec[start++];
        }
    }
    return min_len;
}

int main() {
    vector<int> vec = { 1, 4, 45, 6, 10, 19 };
    cout << smallestSubarray(vec, 51) << endl;
}
