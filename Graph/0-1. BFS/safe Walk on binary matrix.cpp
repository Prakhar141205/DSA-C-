class Solution {
public:
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}} ;

    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();

        // res to store the asnwer initialized to inf 
        // i,j has minimum cost to reach i, j from 0, 0  ;
        vector<vector<int>> res(m, vector<int> (n, INT_MAX));

        res[0][0] = grid[0][0] ;

        deque<pair<int, int>> deq ; // to maintain the monotonicity

        deq.push_back({0, 0}) ;

        while(!deq.empty()) {
            // dist, node
            auto [i, j] = deq.front();
            deq.pop_front() ;

            for(auto& [x, y] : directions) {

                int nr = x + i ;
                int nc = y + j ;

                if(nr < 0 || nr >= m || nc < 0 || nc >= n) continue ;

                if(res[nr][nc] > res[i][j] + grid[nr][nc]) { // res[curr] > res[]
                    res[nr][nc]  =  res[i][j] + grid[nr][nc] ;

                if(grid[nr][nc] == 0 ) {
                    deq.push_front({nr,nc}) ;
                }else {
                    deq.push_back({nr,nc}) ;
                }
                }
            }
        } 

        int minimumHealthToReachEnd = res[m-1][n-1] ;

        return health - minimumHealthToReachEnd >= 1 ; 
    }
};