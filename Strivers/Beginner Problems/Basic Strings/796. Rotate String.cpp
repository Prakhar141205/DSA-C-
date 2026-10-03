class Solution {
public:
    bool rotateString(string s, string goal) {
        int n = s.length();
        int g = goal.length();
        if(n != g) return false;

        int idx = n;
        for(int i=0; i<n; i++) {
            if(s[0] == goal[i]) {
                idx = i;
                break;
            }
        }

        int i = 0;
        while(i < n ) {
            if(s[i] != goal[idx] ) return false;
            i++;
            idx = (idx+1)%g;
        }
        return true;
    }
};