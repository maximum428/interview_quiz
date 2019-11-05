#include <iostream>

using namespace std;

#if 1
#if 1
int WordCount(string str) {
    int start = 0, end = 0, count = 0;
    while (end < str.length()) {
        while (end < str.length() && str[end] == ' ')
            end++;
        start = end;
        while (end < str.length() && str[end] != ' ')
            end++;
        if (start < end)
            count++;
    }
    return count;
}
#else
int WordCount(string str){
    stringstream ss(str);
    string word;
    int count = 0;
    
    while (ss >> word)
        count++;
    return count;
#endif
#else
int WordCount(string str) {
    if (str.length() == 0)
        return 0;
    
    int index = 0, wordCount = 0;
    bool inWord;
    
    while (str.at(index) == ' ' && index < str.length() - 1) {
        index++;
    }
    
    if (str.at(index) == ' ' && index == str.length()) {
        return 0;
    }
    
    while (index < str.length()) {
        if (str.at(index) != ' ') {
            inWord = true;
        } else {
            while (str.at(index) == ' ' && index < str.length() - 1) {
                index++;
            }
            inWord = false;
            wordCount++;
        }
        index++;
    }
    
    if (inWord) {
        wordCount++;
    }
    return wordCount;
}
#endif

int main() {
    string str = "Was it Eliot's toilet I saw";
    
    cout << "Word count: " << WordCount(str) << endl;
}
