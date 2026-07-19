class Solution {
public:
    string smallestSubsequence(string s) {
        int n = s.length();
        vector<int> lastIndex(26, 0);

        for(int i=0; i<n; i++) {
            lastIndex[s[i] - 'a'] = i;
        }

        stack<int> stk;
        unordered_set<char> st;

        for(int i=0; i<n; i++) {
            char ch = s[i];
            if(st.count(ch)) continue;

            while(!stk.empty()) {
                char prev = s[stk.top()];
                if(prev > ch && lastIndex[prev-'a'] > i) {
                stk.pop();
                st.erase(prev);
                }else {
                    break;
                }
            }
            stk.push(i);
            st.insert(ch);
        }

        string ans = "";
        while(!stk.empty()) {
            ans += s[stk.top()];
            stk.pop();
        }
        reverse(ans.begin(), ans.end());

        return ans;        
    }
};