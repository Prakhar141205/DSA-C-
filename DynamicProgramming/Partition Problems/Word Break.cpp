class Solution {
public:
    int n;
    int t[301];

    bool solve(string& s, int i, unordered_set<string>& st) {
        if(i >= n) return true;

        if(t[i] != -1) return t[i];
        if(st.find(s) != st.end()) return true;

        for(int l=1; l<=n; l++) {

            string temp = s.substr(i, l) ;
            if((st.find(temp) != st.end()) && solve(s, i+l, st)) return true;
        }

        return t[i] = false; 
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        n = s.length() ;
        unordered_set<string> st(wordDict.begin(), wordDict.end());
        memset(t, -1, sizeof(t)) ;
        return solve(s, 0, st);
    }
};

// Using the Same template 
class Solution {
public:
    int n;
    int t[301];

    bool solve(string& s, int i, unordered_set<string>& st) {
        if(i >= n) return true;

        if(t[i] != -1) return t[i];
        if(st.find(s) != st.end()) return true;

        for(int l=i; l<n; l++) {

            string temp = s.substr(i, (l-i+1)) ;
            if((st.find(temp) != st.end()) && solve(s, l+1, st)) return true;
        }

        return t[i] = false; 
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        n = s.length() ;
        unordered_set<string> st(wordDict.begin(), wordDict.end());
        memset(t, -1, sizeof(t)) ;
        return solve(s, 0, st);
    }
};