class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        unordered_map<string, int> mp;
        // store each count in the string
        int ans=0;
        bool centreUsed = false;
        int n = words.size();
        for(int i=0; i<n; i++){
            mp[words[i]]++;
        }

        
        for(string& word: words){
            string rev = word;
            reverse(rev.begin(), rev.end());

            if(word != rev){ // rev is not same as word
                if(mp[word] > 0 && mp[rev] > 0){ // agar dono 1 se jyda honge to chalega
                    ans += 4;
                    mp[word]--;
                    mp[rev]--;
                }
            }else{
                if(mp[word] >= 2 ){ // agar rev same as word toh agar cnt 2 se jyada hai toh bhi chalega 
                    ans += 4;
                    mp[word] -= 2;
                }else if(mp[word] == 1 && !centreUsed){
                    ans += 2;
                    mp[word]--;
                    centreUsed = true;
                } 
            }
        }
        return ans;
    }
};