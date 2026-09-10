

class Solution {
public:
    const int mod = 1e9+7 ;
    int m, n ;
    int t[1001][1001];

    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int solve(vector<vector<int>>& grid, int i, int j) {
        if(t[i][j] != -1) return t[i][j];

        int res  = 1 ;

        for(auto [x, y ] : directions) {

            int i_ = i + x;
            int j_ = j + y ;

            if(i_ < 0 or i_ >= m or j_ < 0 or j_ >= n) continue;

            if(grid[i_][j_] < grid[i][j]) {
                res = (res + solve(grid, i_, j_))%mod;
            }
        }

        return t[i][j] = res;
    }
    int countPaths(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        memset(t, -1, sizeof(t));
        int cnt = 0;
        for(int i=0; i<m; i++) {

            for(int j=0; j<n; j++) {

                cnt = (cnt + solve(grid, i, j))%mod;
            }
        }

        return cnt%mod;
        
    }
};