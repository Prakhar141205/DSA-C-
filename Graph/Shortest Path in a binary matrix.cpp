class Solution {
public:
    vector<vector<int>> directions = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}} ;
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int m = grid.size();
        if(grid[m-1][m-1] != 0) return -1; 
        if(grid[0][0] != 0) return -1 ;

        queue<pair<int, int>> que;
        que.push({0, 0}) ;
        grid[0][0] = 1 ;
        int cnt = 1 ;

        while(!que.empty()) {
            int n = que.size() ;
            while(n--) {
            auto [curr_i, curr_j] = que.front();
            que.pop() ;
            if(curr_i == m-1 && curr_j == m-1) return cnt ;

            for(auto& dir : directions) {
                int new_i = curr_i + dir[0];
                int new_j = curr_j + dir[1] ;

                if(new_i >= 0 && new_i < m && new_j >= 0 && new_j < m && grid[new_i][new_j] == 0) {
                    que.push({new_i, new_j});
                    grid[new_i][new_j] = 1 ;
                }
            }
        }
        cnt++ ;
        }
        
        return -1 ;
    }
};