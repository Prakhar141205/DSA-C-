class Solution {
public:
    bool isPalindrome(int x) {

        if(x < 0) return false;

        string t = to_string(x);
        string old = t ;
        reverse(begin(t), end(t));
        
        return t == old ;
    }
};