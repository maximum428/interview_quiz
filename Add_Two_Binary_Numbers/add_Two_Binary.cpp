#include <iostream>

void makeEqualLength(string& str1, string& str2) {
    int len1 = str1.size();
    int len2 = str2.size();
    
    if (len1 == len2) return;
    
    if (len1 < len2) {
        for (int i = 0; i < len2 - len1; i++)
            str1 = '0' + str1;
    } else {
        for (int i = 0; i < len1 - len2; i++)
            str2 = '0' + str2;
    }
}
string add_Two_Binary(string str1, string str2) {
    string result;
    makeEqualLength(str1, str2);
    
    int carry = 0;
    for (int i = str1.size() - 1; i >= 0; i--) {
        int bit1 = str1.at(i) - '0';
        int bit2 = str2.at(i) - '0';
        cout << "bit1: " << bit1 << "; bit2: " << bit2 << endl;
        int sum = (bit1 ^ bit2 ^ carry) + '0';
        cout << "sum: " << sum << endl;
        result += (char)sum; // + result;
        carry = (bit1 & bit2) | (bit1 & carry) | (bit2 & carry);
        cout << "carry: " << carry << endl;
    }
    if (carry)
        result += '1';  // + result;
    return result;
}

int main() {
    string str1 = "1100011", str2 = "10";
    cout << "Sum is " << add_Two_Binary(str1, str2);
}
