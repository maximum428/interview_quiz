vector<int> findDistance(vector<char>& vec, char k) {
    int start = 0;
    vector<int> res(vec.size(), -1);
    
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == k) {
            for (int j = start; j <= i; j++) {
                if (start == 0)
                    res[j] = abs(i-j);
                else
                    res[j] = min(abs(j-start), abs(i-j));
            }
            start = i;
        }
    }
    return res;
}

int main() {
    vector<char> vec = {'f', 'r', 'e', 'e', 'w', 'i', 'r', 'e'};
    char k = 'e';
    
    vector<int> res = findDistance(vec, k);
    for (auto e : res) {
        cout << e << " ";
    }
    cout << "\n";
}
