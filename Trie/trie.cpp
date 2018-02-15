#include <iostream>

struct Trie {
    Trie* c[26];
    int cnt;
    Trie(): cnt(0) {
        memset(c, 0, sizeof(c));
    }
};

Trie* root = new Trie();

void insert(char* s) {
    Trie* ptr = root;

    while (*s) {
        //cout << (*s-'a'+1) << endl;
        if (!ptr->c[*s-'a'+1])
            ptr->c[*s-'a'+1] = new Trie();
        ptr = ptr->c[*s-'a'+1];
        s++;
    }
    ptr->cnt++;
}

int find(char *s) {
    Trie* ptr = root;
    while (*s) {
        if (!ptr->c[*s-'a'+1])
            return 0;
        ptr = ptr->c[*s-'a'+1];
        s++;
    }
    return ptr->cnt;
}

int main() {
    int n = 3, m = 3;
    char* cards[n] = {"sprout", "sprout", "akindofplant"};
    char* asks[m] = {"sprout", "is", "akindofplant"};
    for (int i = 0; i < n; i++) {
        insert(cards[i]);
    }
    for(int i = 0; i < m; i++) {
        cout << asks[i] << ": " << endl;
        cout << find(asks[i]) << endl;
    }
    
    if (root != NULL) {
        cout << "Remove root" << endl;
        delete root;
    }
}
