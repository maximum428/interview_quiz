int countWords(const string& sentence) {
    int wordcount = 0;
    bool inword = false;
    
    if (sentence.empty()) {
        return wordcount;
    }
    
    for (const char& ch : sentence) {
        if (isspace(ch)) {
            if (inWord) {
                inWord = false;
                wordcount++;
            }
        } else if (isalpha(ch) || ch == '-') {
            inWord = true;
        } else if (ch == '.' || ch == ',' || ch == '?' || ch == '!') {
            if (inWord) {
                wordcoun++;
                inWord = false;
            }
        }
    }
    
    if (inWord) {
        wordcount++;
    }
    
    return wordcount;
}
