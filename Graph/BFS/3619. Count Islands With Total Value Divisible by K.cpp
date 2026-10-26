class Solution {
public:
    int m, n;
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    long long bfs(vector<vector<int>>& grid, int i, int j) {
        
        long long sum = 0;
        queue<pair<int, int>> que;
        que.push({i, j});
        sum += grid[i][j];

        grid[i][j] = 0;

        while(!que.empty()) {
            auto [i, j] = que.front();
            que.pop();

            cout << sum << " ";
            for(auto [x, y] : directions) {
                int nx = i + x;
                int ny = j + y;

                if(nx >= 0 and ny >= 0 && nx < m and ny < n && grid[nx][ny] > 0) {
                    que.push({nx, ny});
                    sum = (sum + grid[nx][ny]);
                    grid[nx][ny] = 0;
                }
            }
        }

        return sum;
    }


    int countIslands(vector<vector<int>>& grid, int k) {
        m = grid.size();
        n = grid[0].size();
        int ans = 0;
        

        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {

                if(grid[i][j] > 0) {
                long long cnt = bfs(grid, i, j);
                
                if(cnt > 0 and cnt % k == 0) {
                    ans += 1;
                }
            }
            }
        }
        return ans;
    }
};