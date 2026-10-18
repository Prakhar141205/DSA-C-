class Solution {
public:
    vector<int> lastVisitedCell(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        auto isInvalid = [&](int i, int j) {
            return i < 0 || j < 0 || i >=m || j >= n ;
        } ;
        queue<pair<int, int>> que;

        que.push({0, 0});
        vector<vector<bool>> vis(m, vector<bool> (n, false));
        vis[0][0] = true;
        while(!que.empty()) {
            auto [i, j ] = que.front();
            que.pop();


            if(grid[i][j] == 'R')  {
                if(isInvalid(i,j+1) || vis[i][j+1]) {
                    return {i, j};
                }
                que.push({i, j+1});
                vis[i][j] = true;
            }
            
            else if(grid[i][j] == 'L') {
                
                if(isInvalid(i,j-1) || vis[i][j-1]) {
                    return {i, j};
                }
                que.push({i, j-1});
                vis[i][j] = true;
            }
            else if(grid[i][j] == 'U') {
                if(isInvalid(i-1,j) || vis[i-1][j]) {
                    return {i, j};
                }
                que.push({i-1, j});
                vis[i][j] = true;
            }
            else {
                if(isInvalid(i+1,j) || vis[i+1][j]) {
                    return {i, j};
                }
                que.push({i+1, j});
                vis[i][j] = true;
            }
            
        }

        return {};
    }
};