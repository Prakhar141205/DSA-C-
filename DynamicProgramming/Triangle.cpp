class Solution {
public:
    int m;
    int t[201][201] ;
    int solve(vector<vector<int>>& triangle, int r, int c) {
        if(r == m-1) return triangle[r][c];
        if(t[r][c] != -1) return t[r][c] ;

        return t[r][c] = triangle[r][c] + min(solve(triangle, r+1, c), solve(triangle, r+1, c+1)) ;
    }
    int minimumTotal(vector<vector<int>>& triangle) {
        m = triangle.size();
        memset(t, -1, sizeof(t)) ;
        return solve(triangle, 0, 0) ;
    }
};

class Solution {
public:
    
    int minimumTotal(vector<vector<int>>& triangle) {
        int m = triangle.size() ;
        vector<vector<int>> t = triangle ;

        for(int row = m-2; row >= 0 ; row--) {
            for(int col=0; col <= row; col++) {

                t[row][col] = t[row][col] + min(t[row+1][col], t[row+1][col+1]) ;
            }
        }

        return t[0][0];
    }
};