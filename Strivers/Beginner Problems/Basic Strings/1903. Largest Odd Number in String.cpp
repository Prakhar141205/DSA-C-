class Solution {
public:
    string largestOddNumber(string num) {
        int n = num.length();
        int idx = n;
        for(int i=n-1; i>=0; i--) {
            if((num[i] - '0' ) & 1) {
                idx = i;
                break;
            }
        }

        string ans = num.substr(0, idx+1);
        return idx != n ? ans : "";
    }
};