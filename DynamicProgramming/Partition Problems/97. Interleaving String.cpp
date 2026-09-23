class Solution {
public:
    int m, n, N;
    int t[101][101][201];

    bool solve(string& s1, string& s2, string& s3, int i, int j, int k) {
        if(i == m && j == n && k == N) return true; // when all goes out of bounds simultaneoudly
        if(k >= N) return false; // only k goes out of bounds means atleast one string is not completely used
        if(t[i][j][k] != -1) {
            return t[i][j][k] ;
        }
        bool result = false;
        if(s1[i] == s3[k]) {
            result = solve(s1, s2, s3, i+1, j, k+1);
            if(result) return t[i][j][k] = true;
        }

        if(s2[j] == s3[k]) {
            result = solve(s1, s2, s3, i, j+1, k+1);
            if(result) return t[i][j][k] = true;
        }

        return t[i][j][k] = result;
    }
    bool isInterleave(string s1, string s2, string s3) {
        m = s1.length();
        n = s2.length();
        N = s3.length();
        memset(t, -1, sizeof(t));
        return solve(s1, s2, s3, 0, 0, 0);
    }
};