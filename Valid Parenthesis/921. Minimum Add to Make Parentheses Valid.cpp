class Solution {
public:
    int minAddToMakeValid(string s) {
        // stack<char> s;
        int ans = 0, cnt=0;
        for(int i=0; i<s.length(); i++) {
            if(s[i] == '(') {
                cnt++;
                // s.push(s[i]); 
            }
            else {
                // if(!st.empty()) st.pop();
                if(cnt != 0) cnt--;
                else ans++;
            }
        }
        return ans + cnt;
    }
};