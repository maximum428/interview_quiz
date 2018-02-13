int main() {
    vector<int> stk;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int type, val;
        cin >> type;
        switch (type) {
            case 1: // 1 x  -Push the element x into the stack.
                {
                cin >> val;
                vector<int>::iterator it = stk.begin();
                stk.insert(it, val);
                break;
                }
            case 2:   // -Delete the element present at the top of the stack.
                {
                stk.erase(stk.begin());
                break;
                }
            case 3:   // -Print the maximum element in the stack.
                {
                int max_element = 0;
                for (int i = 0; i < stk.size(); i++) {
                    max_element = max(max_element, stk[i]);
                }
                cout << max_element << endl;
                break;
                }
            default:
                throw invalid_argument("ERROR: Icorrect input");
        }
    }  
    return 0;
}
