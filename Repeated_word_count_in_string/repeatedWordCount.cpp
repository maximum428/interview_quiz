#include <iostream>
#include <set>

using namespace std;

vector<string> splitWords(string str) {
    if (str.length() == 0)
        return {};
    
    int index = 0;
    while (index < str.length() && str.at(index) == ' ') {
        index++;
    }
    
    string word;
    bool inWord;
    vector<string> words;
    while (index < str.length()) {
        if (str.at(index) != ' ') {
            inWord = true;
            word = word + str.at(index);
            index++;
        } else {
            inWord = false;
            words.push_back(word);
            word = "";
            while (index < str.length() && str.at(index) == ' ')
                index++;
            
        }
    }
    if (inWord)
        words.push_back(word);
    return words;
}

int repeatedWordCount(string str) {
    if (str.length() == 0)
        return 0;
    
    set<string> uniques;
    vector<string> words = splitWords(str);
    
    for (auto word : words) {
        uniques.insert(word);
    }
    
    return words.size() - uniques.size();
}

int main() {
    string str = "Was it Eliot's Was toilet I Was saw";
    
    //int repeated = repeatedWordCount(str);
    
    cout << "repeated Word count: " << repeatedWordCount(str) << endl;
}
