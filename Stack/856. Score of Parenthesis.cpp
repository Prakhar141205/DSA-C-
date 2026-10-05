class Solution {
public:
    int scoreOfParentheses(string s) {
        int n = s.length();
        vector<int> ans;
        int score = 0;
        for(int i=0; i<n; i++) {

            if(s[i] == '(') {
                ans.push_back(score);
                score = 0;
            }else { // current closing 
                if( s[i-1] == '(') { // means there is no neste d
                    score = ans.back() + 1;
                }else { // nested parenthesiss
                    score = ans.back() + 2 * score;
                }

                ans.pop_back();
            }
        }

        return score;
    }
};