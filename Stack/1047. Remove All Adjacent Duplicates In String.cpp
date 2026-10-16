class Solution {
public:
    string removeDuplicates(string s) {
        stack<char> st;

        for(auto& c : s) {
            
            if(!st.empty() && st.top() == c) {
                st.pop();
            }
            else st.push(c);
        }   

        string ans = "";
        while(!st.empty()) {
            ans +=  st.top();
            st.pop();
        }
        
        reverse(begin(ans), end(ans));

        return ans;
    }
};

// Using string ans
class Solution {
public:
    string removeDuplicates(string s) {
        string ans = "";

        int i=0; 

        while(i < s.length()) {
            if(ans.empty() || ans.back() != s[i]) {
                ans.push_back(s[i]);
            }else ans.pop_back();

            i++;
        }

        return ans;
    }
};