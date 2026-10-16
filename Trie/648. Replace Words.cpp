class Solution {
public:
    struct TrieNode {
        bool endOfWord;
        TrieNode* children[26];
    };

    TrieNode* getNode() {
        TrieNode* newNode = new TrieNode();

        newNode->endOfWord = false;
        for(int i=0; i<26; i++) {
            newNode->children[i] = nullptr;
        }

        return newNode;
    }
    
    TrieNode* root ;
    void insert(string word) {
        TrieNode* crawler = root;
        for(int i=0; i<word.length(); i++) {
            int idx = word[i] - 'a';
            if(crawler->children[idx] == nullptr) {
                crawler->children[idx] = getNode();
            }

            crawler = crawler->children[idx] ;
        }

        crawler->endOfWord = true;

    }

    string search(string& word) {
        TrieNode* crawler = root;
        for(int i=0; i<word.length(); i++) {
            int idx = word[i] - 'a';
            if(crawler->children[idx] == nullptr) {
                return word;
            }

            crawler = crawler->children[idx] ;
            if(crawler->endOfWord) {
                return word.substr(0, i+1);
            }
        }
        return word;

    }
    string replaceWords(vector<string>& dictionary, string sentence) {
        root  = getNode();

        for(auto w : dictionary) {
            insert(w);
        }

        stringstream ss (sentence);
        string word;
        string result;

        while(getline(ss, word, ' ') ) {
            result += search(word) + " ";
        }

        result.pop_back();

        return result;
    }   
};