class Solution {
public:
    bool isVowel(char ch ) {
        
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ; 
    }

    long long countOfSubstrings(string word, int k) {
        long long  ans=0;
        int n = word.length();

        int cons = 0;
        unordered_map<char, int> mp;

        // get the next consonants index
        vector<int> nextCons(n); 

        int lastConsIdx = n;
        
        // start from the last for optimal storage of next consonants index
        for(int i=n-1; i>=0; --i) {
            nextCons[i] = lastConsIdx;

            if(!isVowel(word[i])) {
                lastConsIdx = i;
            }
        }

        int l=0, r=0;

        while(r < n) {
            char ch = word[r];

            if(isVowel(ch)) {
                mp[ch]++;
            }else {
                cons++;
            } 
            

            // invalid window, move left pointer to make it valid   
            while(cons > k) {
                char ch = word[l];

                if(isVowel(ch)){
                 mp[ch]--;
                 if(mp[ch] == 0) mp.erase(ch); // don't forget to erase the vowel from map if its count is 0    
                } else {
                    cons--;
                }

                l++;
            }

            // valid window and check for more substrings by moving left pointer to right until the window is invalid   graph
            while(l < n && mp.size() == 5 && cons == k) {
                int idx = nextCons[r];

                ans += (idx-r);

                char ch = word[l];

                if(isVowel(ch)) {
                    mp[ch]--;
                    if(mp[ch] == 0) {
                        mp.erase(ch);
                    }
                }else {
                    cons--;
                }

                l++;
            }
            r++;
        }
       return ans; 
    }
};