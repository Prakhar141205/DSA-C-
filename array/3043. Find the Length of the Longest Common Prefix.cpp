// using Trie

class Trie
{
public:
    struct Node
    {
        Node* next[10]={nullptr};
    };

    Trie()
    {
        root=new Node();
    }

    void insert(string str)
    {
        auto curr=root;
        for(char& c:str)
        {
            if(!curr->next[c-'0'])
                curr->next[c-'0']=new Node();
            curr=curr->next[c-'0'];
        }
    }

    int get_prefix_len(string str)
    {
        auto curr=root;
        int len=0;
        for(char& c:str)
        {
            if(!curr->next[c-'0'])
                return len;
            curr=curr->next[c-'0'];
            len++;
        }
        return len;
    }
private:
    Node* root;
};

class Solution 
{
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) 
    {
        Trie trie;
        for(int& val:arr1)
            trie.insert(to_string(val));
        
        int res=0;
        for(int& val:arr2)
        {
            int prefix=trie.get_prefix_len(to_string(val));
            res=max(res,prefix);
        }
        return res;
    }
};

class TrieNode {
public:
    // Each node has up to 10 possible children (digits 0-9)
    TrieNode* children[10];
    TrieNode() {
        for (int i = 0; i < 10; ++i) {
            children[i] = nullptr;
        }
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() { root = new TrieNode(); }

    // Insert a number into the Trie by treating it as a string of digits
    void insert(int num) {
        TrieNode* node = root;
        string numStr = to_string(num);
        for (char digit : numStr) {
            int idx = digit - '0';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
        }
    }

    // Find the longest common prefix for a number in arr2 with the Trie
    int findLongestPrefix(int num) {
        TrieNode* node = root;
        string numStr = to_string(num);
        int len = 0;

        for (char digit : numStr) {
            int idx = digit - '0';
            if (node->children[idx]) {
                // Increase length if the current digit matches
                len++;
                node = node->children[idx];
            } else {
                // Stop if no match for the current digit
                break;
            }
        }
        return len;
    }
};

class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        Trie trie;

        // Step 1: Insert all numbers from arr1 into the Trie
        for (int num : arr1) {
            trie.insert(num);
        }

        int longestPrefix = 0;

        // Step 2: Find the longest prefix match for each number in arr2
        for (int num : arr2) {
            int len = trie.findLongestPrefix(num);
            longestPrefix = max(longestPrefix, len);
        }

        return longestPrefix;
    }
};

class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        unordered_set<string> st;

        for (int x : arr1) {
            string s = to_string(x);
            for (int len = 1; len <= s.size(); len++) {
                st.insert(s.substr(0, len));
            }
        }

        int ans = 0;

        for (int x : arr2) {
            string s = to_string(x);
            for (int len = s.size(); len >= 1; len--) {
                if (st.count(s.substr(0, len))) {
                    ans = max(ans, len);
                    break;
                }
            }
        }

        return ans;
    }
};