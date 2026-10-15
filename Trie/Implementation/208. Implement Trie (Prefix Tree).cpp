class Trie {

public:

    struct TrieNode {
        bool isEndOfWord;
        TrieNode* children[26];
    };

    TrieNode* getNode() {
        TrieNode* newNode = new TrieNode();
        for(int i=0; i<26; i++) {
            newNode->children[i] = nullptr;
        }
        return newNode;
    }

    TrieNode* root;
    Trie() {
        root = getNode();

    }
    
    void insert(string word) {
        TrieNode* crawl = root;
        
        for(auto c : word) {
            int idx = c-'a';
            if(crawl->children[idx] == nullptr) {
                crawl->children[idx] = getNode();
            }
            crawl = crawl->children[idx];
        }
        crawl->isEndOfWord = true;
    }
    
    bool search(string word) {
        TrieNode* crawl = root;
        
        for(auto c : word) {
            int idx = c-'a';
            if(crawl->children[idx] == nullptr) {
                return false;
            }
            crawl = crawl->children[idx];
        }
        return crawl != nullptr && crawl->isEndOfWord;
        
    }
    
    bool startsWith(string prefix) {
        TrieNode* crawl = root;
        
        for(auto c : prefix) {
            int idx = c-'a';
            if(crawl->children[idx] == nullptr) {
                return false;
            }
            crawl = crawl->children[idx];
        }
        return true;
        
    }
};
