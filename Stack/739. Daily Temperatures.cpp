class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& ts) {
        int n = ts.size();
        vector<int> ans (n, 0);
        stack<pair<int, int>> st; // {val, indes}
        for(int i=n-1; i>=0; i--) {

            while(!st.empty() && st.top().first <= ts[i]) {
                st.pop();
            }

            if(!st.empty()){
                ans[i] = st.top().second - i ;
            }

            st.push({ts[i], i});
        }
        return ans;
    }
};

// Using monotonic stack without pair
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& ts) {
        int n = ts.size();
        vector<int> ans (n, 0);
        stack<int> st; // store index
        for(int i=n-1; i>=0; i--) { 

            while(!st.empty() && ts[st.top()] <= ts[i]) {
                st.pop();
            }

            if(!st.empty()){
                ans[i] = st.top() - i ;
            }

            st.push(i);
        }
        return ans;
    }
};
