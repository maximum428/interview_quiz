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
        result = (char)sum + result;
        carry = (bit1 & bit2) | (bit1 & carry) | (bit2 & carry);
        cout << "carry: " << carry << endl;
    }
    //if (carry)
    //    result = '1' + result;
    return carry ? '1' + result : result;
}

int add_two_binary(int x, int y){
    int carry = 0, res = 0;
    for (int i = 0; i < 32; i++, x >>= 1, y >>= 1) {
        int bit1 = x & 1;
        int bit2 = y & 1;
        int sum = (bit1 ^ bit2 ^ carry);
        res |= sum << i;
        carry = (bit1 & bit2) | (bit1 & carry) | (bit2 & carry);
    }
    return carry ? res |= 1 << 32 : res;
}

int main() {
    string str1 = "1100011", str2 = "10";
    cout << "Sum is " << add_Two_Binary(str1, str2);
    
    int x = 5, y = 3;
    cout << "Sum is " << bitset<32>(add_two_binary(x, y)) << endl;
}
