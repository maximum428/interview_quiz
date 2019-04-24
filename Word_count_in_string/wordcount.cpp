#include <iostream>

using namespace std;

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

int main() {
    string str = "Was it Eliot's toilet I saw";
    
    cout << "Word count: " << WordCount(str) << endl;
}
