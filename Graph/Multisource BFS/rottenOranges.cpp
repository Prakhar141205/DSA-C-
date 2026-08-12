class Solution {
public:
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}} ;

    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        queue<pair<int, int>> que ;
        int freshOranges = 0;
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {

                if(grid[i][j] == 2) {
                    que.push({i, j});
                }else if(grid[i][j] == 1) {
                        freshOranges++;
                    }
            }
        }

        if(freshOranges == 0) return 0 ;


        int cost = 0;
        // int freshOranges = ;
        while(!que.empty()) {
            int t = que.size() ;
            
            while(t--) {
                auto [i, j] = que.front();
                que.pop();

                for(auto [x, y] : directions) {
                    int n_i = x + i ;
                    int n_j = y + j ;

                    if(n_i >= 0 && n_i < m && n_j >= 0 && n_j < n && grid[n_i][n_j] == 1) {
                        grid[n_i][n_j] = 2 ;
                        que.push({n_i, n_j}) ;
                        freshOranges--;
                    }
                }
            }
            cost++;
        }
        return freshOranges == 0 ? cost-1  : -1 ;
    }
};