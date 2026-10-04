class Solution {
public:
    int n ;
    int t[101][101];
    bool solve(string& s, int idx, int open) {
        if(idx >= n) return open == 0;
        if(t[idx][open] != -1) return t[idx][open];

        bool isValid = false;
        if(s[idx] == '(') {
            isValid = solve(s, idx+1, open+1);
        }else if(s[idx] == '*') {
            isValid |= solve(s, idx+1, open+1);
            isValid |= solve(s, idx+1, open);
            if(open > 0)
                isValid |= solve(s, idx+1, open-1);
        }else if(open > 0) 
            isValid |= solve(s, idx+1, open-1);

        return t[idx][open] = isValid;
    }
    bool checkValidString(string s) {
        n = s.length();
        memset(t, -1, sizeof(t));
        return solve(s, 0, 0);
    }
};