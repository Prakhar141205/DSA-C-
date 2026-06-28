// with sorting 
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n = strs.size();
        vector<vector<string>> ans;
        
        unordered_map<string, vector<string> > mp;

        for(auto& s : strs){
            string temp = s;
            sort(s.begin(), s.end());
            mp[s].push_back(temp);
        }

        for(auto& s : mp){
            ans.push_back(s.second);
        }

        return ans;
        
    }
};

// using counting sort

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n = strs.size();
        vector<vector<string>> ans;

        // sorted string, all valid anagrams 
        // to reduce the time complexity we use counting sort
        unordered_map<string, vector<string> > mp;

        // loop  on the given strings
        for(auto& s : strs){
            // cnt vector to store the count of char in string s
            vector<int> freq(26, 0);
            //  store the char count
            for(auto& c : s){
                freq[c - 'a']++;
            }

            // get the sorted string of s
            string sorted_s="";
            for(int i=0; i<26; i++){
                
                while(freq[i]--){
                    char x = i;
                    sorted_s += x;
                    // freq[i]--
                }
            }
            // store the anagrams
            mp[sorted_s].push_back(s);
        }

        // get into the result vector
        for(auto& st : mp){
            ans.push_back(st.second);
        }

        return ans;
        
    }
};