
void printNames(vector<string> &names) {
    cout << "Names: ";
    for_each (names.begin(), names.end(), [](const string& name) {
        cout << name << ", ";
    });
    cout << '\n';
}

int findLogestNonRepeat2(string *names, int size) {
    unsigned long ans = 0, start = 0;
    vector<string> founds;
    unordered_map<int, unsigned long> mp;
    founds.push_back(names[0]);
    
    for (auto i = 0; i < size - 1; i++) {
        for (auto j = i + 1; j < size; j++) {
            if (find(founds.begin(), founds.end(), names[j]) != founds.end()) {
                mp[start] = founds.size();
                ans = max(ans, founds.size());
                break;
            } else {
                founds.push_back(names[j]);
            }
        }
        start = i + 1;
        founds.clear();
        founds.push_back(names[i+1]);
    }
    
    auto m = max_element(mp.begin(), mp.end(), [](decltype(mp)::value_type& l, decltype(mp)::value_type& r) -> bool {
        return l.second < r.second;
    });
    
    vector<string> newVec(names+m->first, names+m->second);
    printNames(newVec);
    return ans;
}

int findLongestNonRepeat(vector<string>& names) {
    unsigned long ans = 0, start = 0;
    vector<string> founds;
    unordered_map<int, unsigned long> mp;
    founds.push_back(names[0]);
    
    for (int i = 0; i < names.size()-1; i++) {
        for (int j = i+1; j < names.size(); j++) {
            if (find(founds.begin(), founds.end(), names[j]) != founds.end()) {
                mp[start] = j - start; //founds.size();
                ans = max(ans, j - start);  // or ans = max(ans, founds.size()) works too.
                //ans = max(ans, founds.size());
                break;
            } else {
                founds.push_back(names[j]);
            }
        }
        start = i+1;
        founds.clear();
        founds.push_back(names[i+1]);
    }

    auto m = max_element(mp.begin(), mp.end(), [](decltype(mp)::value_type& l, decltype(mp)::value_type& r) -> bool {
       return l.second < r.second; 
    });
    
    vector<string> newVec(names.begin()+m->first, names.begin()+m->second);
    printNames(newVec);
    return ans;
}

int findLengthOfLCIS(vector<int>& nums) {
    int ans = 0, start = 0;
    for (auto i = 1; i < nums.size(); i++) {
        if (nums[i] <= nums[i-1])
            start = i;
        ans = max(ans, i - start +1);
    }
    return ans;
}

int findLengthOfLCIS2(int* nums, int size) {
    int ans = 0, start = 0;
    for (int i = 1; i < size; i++) {
        if (nums[i] <= nums[i-1])
            start = i;
        ans = max(ans, i - start + 1);
    }
    return ans;
}


int main() {
    vector<int> vec = { 1, 3, 5, 4, 7 };
    int nums[] = {1, 3, 5, 4, 7};
    cout << findLengthOfLCIS(vec) << endl;
    cout << findLengthOfLCIS2(nums, sizeof(nums)/sizeof(int)) << endl;
    
    vector<string> names = {"Alison", "Alina", "Alex", "Aileen", "Alex"};
    cout << findLongestNonRepeat(names) << endl;
    
    string names2[] = {"Alison", "Alina", "Alex", "Aileen", "Alex"};
    
    cout << findLogestNonRepeat2(names2, sizeof(names2)/sizeof(string)) << endl;
    
    return 0;
}
