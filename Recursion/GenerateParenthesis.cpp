class Solution {
public:
    vector<string> ans;
    bool isValid(string curr) {
        int cnt = 0 ;
        for(char x : curr) {
            if(x == '(') {
                cnt++;
            }else {
                cnt--;
            }

            if(cnt < 0) return false;
        }

        return cnt == 0 ;
    }
    void solve(string& curr, int n) {
        if(curr.length() == 2*n) {
            if(isValid(curr)) {
                ans.push_back(curr);
            }

            return;
        }

        curr.push_back('(');
        solve(curr, n);
        curr.pop_back();

        curr.push_back(')');
        solve(curr, n);
        curr.pop_back();

    }
    vector<string> generateParenthesis(int n) {
        string curr = "";
        solve(curr, n);

        return ans;
        
    }
};

//  slight optimization by inserting only the valid strings
class Solution {
public:
    vector<string> ans;
    
    void solve(string& curr, int n, int open, int close) {
        if(curr.length() == 2*n) {
           
            ans.push_back(curr);
            return;
        }

        if(open < n) {
            curr.push_back('(');
            solve(curr, n, open+1, close);
            curr.pop_back();
        }

        if(close < open) {
            curr.push_back(')');
            solve(curr, n, open, close+1);
            curr.pop_back();
        }
    }
    vector<string> generateParenthesis(int n) {
        string curr = "";
        int open = 0, close= 0;
        solve(curr, n, open, close);

        return ans;
        
    }
};