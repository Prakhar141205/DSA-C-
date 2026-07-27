class Solution {
public:
    int m, n ;
    void dfs(vector<vector<int>>& grid, int i, int j) {
        if(i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 1)  return ;

        grid[i][j] = 1;

        dfs(grid, i, j+1);
        dfs(grid, i, j-1);
        dfs(grid, i+1, j);
        dfs(grid, i-1, j);
    }
    int closedIsland(vector<vector<int>>& grid) {   
        m = grid.size();
        n = grid[0].size() ;

        for(int r=0; r < m; r++) {
            if(grid[r][0] == 0) {
                dfs(grid, r, 0);
            }

            if(grid[r][n-1] == 0) {
                dfs(grid, r, n-1);
            }
        }


        for(int c=0; c<n; c++) {
            if(grid[0][c] == 0 ){
                dfs(grid, 0, c) ;


            }

            if(grid[m-1][c] == 0) {
                dfs(grid, m-1, c);
            }
        }
        int cnt = 0;
        for(int i=0; i<m; i++) {
            for(int j=0; j < n; j++) {

                if(grid[i][j] == 0) {
                    dfs(grid, i, j);
                    cnt++;
                }
            }
        }

        return cnt ;
        
    }
};