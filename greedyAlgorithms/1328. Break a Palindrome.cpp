class Solution {
public:
    string breakPalindrome(string palindrome) {
        int n = palindrome.size();

        if(n <= 1) return "";
        int l=0;
        
        while(l < n/2){
            if(palindrome[l] != 'a'){
                palindrome[l] = 'a';
                return palindrome;
            }
            l++;
            
        }
        // all characters in the string is 'a'
        palindrome[n-1] = 'b';
        
        return palindrome;
    }
};