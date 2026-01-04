#include <iostream>
#include <cstring>

using namespace std;
using namespace std::string_literals;

struct Trie {
    int cnt;
    Trie* c[26];
    Trie() : cnt(0) {
        memset(c, 0, sizeof(c));
    }
};

Trie* root = new Trie();

void insert(const char* s) {
    Trie *ptr = root;
    
    while (*s) {
        int idx = *s - 'a';
        if (idx < 0 || idx >= 26) return;
        if (!ptr->c[idx])
            ptr->c[idx] = new Trie();
        ptr = ptr->c[idx];
        s++;
    }
    ptr->cnt++;
}

int find(const char *s) {
    Trie *ptr = root;
    while (*s) {
        int idx = *s - 'a';
        if (idx < 0 || idx >= 26) return 0;
        if (!ptr->c[idx])
            return 0;
        ptr = ptr->c[idx];
        s++;
    }
    return ptr->cnt;
}

void freeTrie(Trie* node) {
    if (!node) return;
    for (int i = 0; i < 26; i++) {
        freeTrie(node->c[i]);
    }
    delete node;
}

int main(int argc, char** argv) {
    const char* cards[] = {"sprout", "sprout", "akindofplant"};
    const char* asks[]  = {"sprout", "is", "akindofplant"};
    for (auto s : cards) {
        insert(s);
    }
    for (auto s : asks) {
        cout << s << ": " << find(s) << endl;
    }
    
    freeTrie(root);
    return 0;
}
