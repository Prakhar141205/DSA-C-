class Solution {
public:
    struct TrieNode {
        int cnt;
        TrieNode* cs[26];
    };
    TrieNode* getNode() {
            TrieNode* root = new TrieNode();
            root->cnt = 0;
            for(int i=0; i<26; i++) {
                root->cs[i] = nullptr;
            }
            return root;
    }

    void insert(TrieNode* root, string& word) {
        TrieNode* crawl = root;
        for(auto& c : word) {
            int i = c - 'a';
            if(crawl->cs[i] == nullptr) {
                crawl->cs[i] = getNode();
            }
            crawl->cs[i]->cnt += 1;
            crawl = crawl->cs[i];
        }
    }

    int getScore(TrieNode* root, string& pre) {
        int ans = 0;
        TrieNode* crawl = root;

        for(auto& c : pre) {
            int i = c-'a';
            if(crawl->cs[i] == nullptr) {
                return 0;
            }
            crawl = crawl->cs[i];
        }

        return crawl->cnt;


    }
    int prefixCount(vector<string>& words, string pref) {
        TrieNode* root = getNode();

        for(auto& word : words) {
            insert(root, word);
        }

        return getScore(root, pref);
    }
};



// Best implementation

struct TrieNode {
        int cnt;
        TrieNode* cs[26];
    
    TrieNode() {
        cnt = 0;
        for(int i=0; i<26; i++) {
            cs[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;
    TrieNode* getNode() {
        return new TrieNode();

    }
public:
    Trie() {
        root = getNode();
    }

    void insert(string& word) {
        TrieNode* crawl = root;
        for(auto& c : word) {
            int i = c - 'a';
            if(crawl->cs[i] == nullptr) {
                crawl->cs[i] = getNode();
            }
            crawl->cs[i]->cnt += 1;
            crawl = crawl->cs[i];
        }
    }

    int getScore(string& pre) {
        int ans = 0;
        TrieNode* crawl = root;

        for(auto& c : pre) {
            int i = c-'a';
            if(crawl->cs[i] == nullptr) {
                return 0;
            }
            crawl = crawl->cs[i];
        }

        return crawl->cnt;


    }

};
class Solution {
public:
    
    int prefixCount(vector<string>& words, string pref) {
        Trie trie;

        for(auto& word : words) {
            trie.insert(word);
        }

        return trie.getScore(pref);
    }
};