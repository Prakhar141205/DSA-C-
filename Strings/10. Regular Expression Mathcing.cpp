class Solution {
public:
    bool solve(string s, string p) {
        if(p.length() == 0) return s.length() == 0;

        bool first_char_matched = false;

        if(s.length() > 0 && (s[0] == p[0] || p[0] == '.')) first_char_matched = true;

        if(p[1] == '*') {
            bool not_take = solve(s, p.substr(2));

            bool take = (first_char_matched) && solve(s.substr(1), p);

            return take || not_take;
        }
        
        return first_char_matched && solve(s.substr(1), p.substr(1));
    }
    bool isMatch(string s, string p) {
        return solve(s, p);
        
    }
};

// using two pinters
class Solution {
public:
    bool solve(int i, int j, string s, string p) {
        if(p.length() == j) return s.length() == i;

        bool first_char_matched = false;

        if(s.length() > i && (s[i] == p[j] || p[j] == '.')) first_char_matched = true;

        if(p[j+1] == '*') {
            bool not_take = solve(i, j+2, s, p);

            bool take = (first_char_matched) && solve(i+1, j, s, p);

            return take || not_take;
        }
        
        return first_char_matched && solve(i+1, j+1, s, p);
    }
    bool isMatch(string s, string p) {
        return solve(0, 0, s, p);
        
    }
};