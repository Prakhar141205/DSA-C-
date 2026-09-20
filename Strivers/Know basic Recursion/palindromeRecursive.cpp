class Solution {
public:
    bool isValid(char c ) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
    }
    bool solve(string& s, int i, int j) {
        if(i >= j) return true;

        if(s[i] != s[j]) return false;
        
        return solve(s, i+1, j-1);
    }

    bool isPalindrome(string s) {
        
        string temp = "";

        for(char c : s) {
            if(isValid(c)) {
                cout << c << " ";
                temp += ((c <= '0' && c >= '9') ? c : tolower(c)) ;
            }
        }

        cout << temp << " ";
        return solve(temp, 0, temp.length()-1);
        
    }
};