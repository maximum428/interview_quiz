#include <iostream>

using namespace std;

int strToInt(string num) {
    if (num.length() == 0) return -1;
    
    int pos = 1, result = 0;
    for (int i = num.length()-1; i >= 0; i--) {
        int n = num.at(i) - '0';
        result = result + (n * pos);
        pos *= 10;
    }
    return result;
}
int main() {
    string str = "356";
    cout << strToInt(str) << endl;
}
