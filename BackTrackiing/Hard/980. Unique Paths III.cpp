class Solution {
public:
    int m;
    int n;
    vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}} ;
    int paths;
    int nonObstacles;

    void dfs(vector<vector<int>>& grid, int cnt, int i, int j) {

        if(i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == -1) return ;

        if(grid[i][j] == 2) {
            if(nonObstacles == cnt) paths += 1 ;
            return ;
        }
        
        grid[i][j] = -1 ;
        for(auto& dir : directions) {
            int new_i = i + dir[0];
            int new_j = j + dir[1] ;

           dfs(grid, cnt+1, new_i, new_j);
        }

        grid[i][j] = 0 ;
        return ; 
    }
    int uniquePathsIII(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size() ;
        int x, y ;

        paths = 0;
        nonObstacles = 0 ;
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == 1) {
                    x = i ;
                    y = j ;
                }

                if(grid[i][j] == 0) {
                    nonObstacles++;
                }
            }
        }

        int cnt = 0;
        nonObstacles += 1 ;
        dfs(grid, cnt, x, y) ;

        return paths ;
        
    }
};