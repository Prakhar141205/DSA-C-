class Solution {
public: 
    vector<string> ans ;
    bool isValidPS(string curr) {
        int cnt = 0;

        for(auto& c : curr) {
            if(c == '(') {
                cnt++;
            }else {
                cnt--;
                if(cnt < 0) return false;
            }
        }

        return cnt == 0;
    }
    
    void solve(int n, int cnt, string& curr) {
        if(cnt >= 2*n) {
            
            if(isValidPS(curr)){
                cout << curr << " ";
                ans.push_back(curr);
            }
            return ;
        } 

        curr.push_back('(');
        solve(n, cnt+1, curr);
        curr.pop_back();

        curr.push_back(')');
        solve(n, cnt+1, curr);
        curr.pop_back();
    }
    vector<string> generateParenthesis(int n) {
        string curr = "";
        solve(n, 0, curr);
        return ans;
    }
};