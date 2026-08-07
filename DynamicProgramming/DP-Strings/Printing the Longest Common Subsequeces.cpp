class Solution {
public:
    int longestCommonSubsequence(string s1, string s2) {
        int m = s1.length();
        int n = s2.length();

        vector<vector<int>> t(m+1, vector<int>(n+1, 0)) ;

        // fill first row and col to 0 ;

        for(int i=1; i<= m; i++) {
            for(int j=1; j<=n; j++) {
                if(s1[i-1] == s2[j-1]) {
                    t[i][j] = 1 + t[i-1][j-1] ;
                }else {
                    t[i][j] = max(t[i-1][j], t[i][j-1]) ;
                }
            }
        }
        
        // printing the LCS
        string lcs = "";
        int i = m, j = n;

        while(i > 0 && j > 0) {
            if(s1[i-1] == s2[j-1]) {
                lcs.push_back(s1[i-1]) ;
                i--;
                j--;
            }else {
                if(t[i-1][j] > t[i][j-1]) {
                    i--;
                }else {
                    j--;
                }
            }
        }

        reverse(begin(lcs), end(lcs)) ;

        cout << lcs << "\n"; 
        return t[m][n] ;
    }
};