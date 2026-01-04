#include <bits/stdc++.h>

using namespace std;

class WordDictionary {
private:
    struct TrieNode {
        bool isWord;
        TrieNode* children[26];
        TrieNode() : isWord(false) {
            memset(children, 0, sizeof(children));
        }
    };
    
    TrieNode* root;
    
    bool dfs(string& word, int index, TrieNode* node) {
        if (!node) return false;
        
        if (index == word.length()) {
            return node->isWord;
        }
        
        char c = word[index];
        if (c != '.') {
            return dfs(word, index + 1, node->children[c - 'a']);
        } else {
            for (int i = 0; i < 26; i++) {
                if (node->children[i] && 
                   dfs(word, index + 1, node->children[i])) {
                    return true;
                }
            }
            return false;
        }
    }
    
    void freeTrie(TrieNode* node) {
        if (!node) return;
        for (int i = 0; i < 26; i++) {
            freeTrie(node->children[i]);
        }
        delete node;
    }
public:
    WordDictionary() {
        root = new TrieNode();
    }
    
    virtual ~WordDictionary() {
        freeTrie(root);
    }
    
    void addWord(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
        }
        node->isWord = true;
    }
    
    bool search(string word) {
        return dfs(word, 0, root);
    }
};

int main(int argc, char** argv) {
    WordDictionary wordDictionary;
    wordDictionary.addWord("bad");
    wordDictionary.addWord("bad");
    wordDictionary.addWord("mad");
    cout << wordDictionary.search("pad") << endl;  // return false
    cout << wordDictionary.search("bad") << endl;  // return true
    cout << wordDictionary.search(".ad") << endl;  // return true
    cout << wordDictionary.search("b..") << endl;  // return true
    
    return 0;
}
