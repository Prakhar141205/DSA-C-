
class Solution {
public:
    string smallestPalindrome(string s) {
        int arr[26];

        int n =s.length();
        if(n == 1) return s ;
        // unordered_map<char, int> mp;

        for(auto& c : s) {
            arr[c - 'a']++;
        }

        char e = '*';
        string ans = "";
       
        for(int i=0; i<26; i++) {
            char ch = i + 'a' ;
            if(arr[i] & 1) {
                e = ch;
            }
            int l = arr[i] / 2 ;
            while(l > 0) {
                ans += ch ;
                l--;
            }
        }
        string temp = ans ;

        if(e != '*') ans += e ;
        
       
        reverse(temp.begin(), temp.end());

        ans += temp ;

        return ans; 
    }
};