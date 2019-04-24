#include <iostream>

using namespace std;

bool IsPalindrome(string str) {
    if (str.length() <= 1)
        return false;
    
    int left = 0, right = str.length() - 1;
    
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    while (str.at(left) == str.at(right) && left < right) {
        left++;
        while (str.at(left) < 'A' || str.at(left) > 'Z')
            left++;
        right--;
        while (str.at(right) < 'A' || str.at(right) > 'Z')
            right--;
    }

    return str.at(left) == str.at(right);
}

int main() {
    string str = "Was it Eliot's toilet I saw";
    
    if (IsPalindrome(str))
        cout << "Palindrome" << endl;
    else
        cout << "Not palindrome" << endl;
}
