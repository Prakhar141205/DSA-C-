class Solution {
public:
    int m, n;
    int dp[1001][1001];

    int solve(vector<vector<int>>& grid, int i, int j, int currans) {

        if(i >= m || j >= n) {
            return INT_MAX;
        }
        if(dp[i][j] != -1 ) return dp[i][j];

        if(i == m - 1 and j == n-1) {
            
            return currans ^ grid[i][j]; 
        }

        return dp[i][j] = min(solve(grid, i+1, j, currans ^ grid[i][j])
                    ,solve(grid, i, j+1, currans ^ grid[i][j]));



    }
   

    int minCost(vector<vector<int>>& grid) {
         m = grid.size();
         n = grid[0].size();
         memset(dp, -1, sizeof(dp));

        return solve(grid, 0, 0, 0);
       

        }
};