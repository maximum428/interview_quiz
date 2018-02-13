#include<stdio.h>

int compare_str(const void* a, const void* b) {
    const char **ia = (const char**)a;
    const char **ib = (const char**)b;
    
    return strcmp(*ia, *ib);
}

bool find(char* s, char** built) {
    int i=0;
    char* str = (char*)malloc(sizeof(char));
    strncpy(str, s, strlen(s)-1);
    while (built[i]) {
        if (strcmp(str, built[i]) == 0)
            return true;
        i++;
    }
    return false;
}

char* longestWord(char** words, int wordsSize) {
    int i;
    char* res = (char*)malloc(sizeof(char));
    char** built = (char**)malloc(wordsSize * sizeof(char*));
    qsort(words, wordsSize, sizeof(char*), compare_str);
    for (i = 0; i < wordsSize; i++) {
        if ((strlen(words[i]) == 1) || find(words[i], built)) {
            if (strlen(words[i]) > strlen(res))
                strcpy(res, words[i]);
            built[i] = (char*)malloc(sizeof(char));
            strcpy(built[i], words[i]);
        }
    }
    return res;
}
