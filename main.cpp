#include <bits/stdc++.h>
using namespace std;
class TrieNode {
public:

    bool eow;

    TrieNode* children[26];


    TrieNode() {
        eow = false;

        for(int i=0; i<26; i++) {
            children[i] = nullptr;
        }
    }

    void insert(string s) {

        TrieNode* newNode = this;
        for(auto& c : s) {

            int idx = c - 'a';

            if(newNode->children[idx] == nullptr) {
                newNode->children[idx] = new TrieNode();
            }

            newNode = newNode->children[idx];
        }

        newNode->eow = true;
    }

    string search(string word) {
        TrieNode* crawler = this;

        for(int i=0; i<word.length(); i++) {
            int idx = word[i] - 'a';

            if(crawler->children[idx] == nullptr) return word;
            crawler = crawler->children[idx];

            if(crawler->eow) return word.substr(0, i+1);
        }
        return word;
    }

};


int main() {
    TrieNode* root = new TrieNode();

    root->insert("cat");
    root->insert("bat");

    cout << root->search("cattle") << endl;  // cat
    cout << root->search("battery") << endl; // bat
    cout << root->search("dog") << endl;     // dog
}