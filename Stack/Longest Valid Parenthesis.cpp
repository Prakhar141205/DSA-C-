class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        int res = 0;
        st.push(-1);

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();
                if (st.empty())
                    st.push(i);
                else
                    res = max(res, i - st.top());
            }
        }
        return res;
    }
};


class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.length();
        int open = 0;
        int close = 0;

        int ans = 0;

        for(int i=0; i<n; i++) {
            if(s[i] == ')') close++;
            else open++;

            if(open == close) ans = max(ans, close + open);
            else if(close > open) open = close = 0;
        }

        open = close = 0;
        for(int i=n-1; i>=0; i--)  {

            if(s[i] == ')') close++;
            else open++;
            
            if(open == close) ans = max(ans, close + open);
            else if(open > close) open = close = 0 ;
        }
        return ans; 
    }
};