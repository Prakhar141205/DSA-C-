class Solution {
public:
    vector<pair<int, int>> directions = {{0,1}, {0, -1}, {-1, 0}, {1, 0}, {-1, 1}, {1, 1}, {1, -1}, {-1, -1}};

    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();  
        if(grid[0][0] == 1) return -1;
        queue<pair<int, int>> que;
        int cost = 0;
        que.push({0, 0});

        while(!que.empty()) {

            int t = que.size();

            while(t--) {

                auto [i, j] = que.front();
                que.pop();
                
                if(i == n-1 and j == n-1 ) return cost+1 ;

                for(auto [x, y ] : directions) {
                    int nx = x + i;
                    int ny = y + j ;

                    if(nx < 0 or ny < 0 or nx >= n or ny >= n or grid[nx][ny] == 1) {
                        continue;
                    }

                    grid[nx][ny] = 1 ;
                    que.push({nx, ny});

                }
            }

            cost++;
        }

        return -1 ;

    }

};