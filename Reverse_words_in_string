#include <iostream>
#includde <string>

using namespace std;

string result;

void ReverseWords(string str) {
    if (str.length() == 0 || str.find(" ") == string::npos)
        return;
    
    int last = str.length() - 1;
    int start = last;
    
    while (last >= 0) {
        while (start >=0 && str.at(start) == ' ')
            start -= 1;
        last = start;
        while (start >= 0 && str.at(start) != ' ')
            start -= 1;
        for (int i = start + 1; i <= last; i++) {
            result = result + str.at(i);
        }       
        //cout << "Result: " << result << endl;
        if (start > 0) {
            result = result + ' ';
        }
        last = start - 1;
        start = last;
    }
    if (str.at(str.length() - 1) == ' ')
        result = result.substr(0, str.length() - 2);
}

int main() {
    //char *words = "Hello, This is Alex Chang   ";
    //char ws[] = "Hello, This is Alex Chang";
    string words = "Hello, this is Alex Chang  ";
    
    ReverseWords(words);
    cout << "Result: " << result << endl;
    return 0;
}
