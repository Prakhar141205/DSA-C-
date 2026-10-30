struct TrieNode {
        int cnt = 0;
        TrieNode* children[26] ;
};
class Solution {
public:
    TrieNode* getNode() {
        TrieNode* root = new TrieNode();

        root->cnt = 0;

        for(int i=0; i<26; i++) {
            root->children[i] = nullptr;
        }
        return root;
    }

    void insert(string s, TrieNode* root) {
        TrieNode* crawler = root;

        for(auto c : s) {
            int idx = c-'a';

            if(crawler->children[idx] == nullptr) {
                crawler->children[idx] = getNode();
            }

            crawler->children[idx]->cnt += 1;
            

            crawler = crawler->children[idx] ;
        }
    }
    int getPrefixScoreSum(string& curr, TrieNode* root) {
        TrieNode* crawler = root;
        int score = 0;
        for(auto& c : curr) {
            int idx = c - 'a';
            if(crawler->children[idx] != nullptr) {
                    score += crawler->children[idx]->cnt ;
            }else {
                break;
            }
            crawler = crawler->children[idx];
        }

        return score;
    }
    vector<int> sumPrefixScores(vector<string>& words) {
        int n = words.size();
        TrieNode* root = getNode();

        vector<int> ans(n, 0);

        for(auto word : words) {
            insert(word, root);
        }
        for(int i=0; i<n; i++) {

            ans[i] = getPrefixScoreSum(words[i], root) ;
        }
        return ans;
    }
};