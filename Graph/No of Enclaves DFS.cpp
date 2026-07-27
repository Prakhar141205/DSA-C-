class Solution {
public:
    int m, n ;
    void dfs(vector<vector<int>>& grid, int i, int j){
        if(i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0) return ;

        grid[i][j] = 0 ; //marked visited 
        dfs(grid, i, j+1); // right
        dfs(grid, i, j-1); // left 
        dfs(grid, i+1, j);  // down
        dfs(grid, i-1, j);  // up
    
    }

    // approach : start from the boundary and mark all the possible where dfs can go 
    // and after having dfs from all the boundary only the 1's that are answer remains in the grid ;
    int numEnclaves(vector<vector<int>>& grid) {
         m = grid.size();
         n = grid[0].size() ;

        for(int row=0; row<m; row++) {
            if(grid[row][0] == 1) {
                dfs(grid, row, 0) ;
            }

            if(grid[row][n-1] == 1) {
                dfs(grid, row, n-1) ;
            }
        }


        for(int col = 0; col < n; col++) {
            
            if(grid[0][col] == 1) {
                dfs(grid, 0, col) ;
            }

            if(grid[m-1][col] == 1) {
                dfs(grid, m-1, col) ;
            }
        }
        int cnt = 0;
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == 1) cnt++;
            }
        }

        return cnt ;
    }
};