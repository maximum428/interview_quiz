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

string addBinary(string a, string b) {
    string res;
    int carry = 0, ac = a.length() - 1, bc = b.length() - 1;
        
    while (ac >= 0 || bc >= 0 || carry == 1) {
        if (ac >= 0)
            carry += a[ac--] - '0';
        if (bc >= 0)
            carry += b[bc--] - '0';
        res = (char)(carry % 2 + '0') + res;
        carry /= 2;
    }
    return res;
}

bool makeEqualLength2(string& a, string& b) {
    int a_pos = a.find('.'), b_pos = b.find('.');
    if (a_pos == string::npos || b_pos == string::npos) return false;
    int alen = a.length() - a_pos, blen = b.length() - b_pos;

    if (alen > blen) {
        for (int i = 0; i < alen - blen; i++) {
            b = b + '0';
        }
    } else if (blen > alen) {
        for (int i = 0; i < blen - alen; i++) {
            a = a + '0';
        }
    }
    
    if (a_pos > b_pos) {
        for (int i = 0; i < a_pos - b_pos; i++) {
            b = '0' + b;
        }
    } else {
        for (int i = 0; i < b_pos - a_pos; i++) {
            a = '0' + a;
        }
    }
    
    return true;
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

string addFloat(string a, string b) {
    string res = "";
    if (a.size() == 0) return b;
    if (b.size() == 0) return a;
    
    if (!makeEqualLength2(a, b)) return res;

    int sum = 0;
    for (int i = a.length() - 1; i >= 0; i--) {
        if (a[i] == '.') {
            res = '.' + res;
            continue;
        }
        sum += (a[i] - '0') + (b[i] - '0');
        res = (char)(sum % 10 + '0') + res;
        sum /= 10;
    }

    return sum != 0 ? '1' + res : res;
}

int main() {
    string str1 = "1100011", str2 = "10";
    cout << "Sum is " << add_Two_Binary(str1, str2);
    
    int x = 5, y = 3;
    cout << "Sum is " << bitset<32>(add_two_binary(x, y)) << endl;
    
    str1 = "2.32"; str2 = "14.7";
    cout << "Sum is " << addFloat(str1, str2) << endl;
}
