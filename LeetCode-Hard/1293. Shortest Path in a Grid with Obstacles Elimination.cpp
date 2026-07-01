class Solution {
public:
    vector<vector<int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        queue<vector<int>> que;
        bool vis[41][41][1601];
        memset(vis, false, sizeof(vis));
        int steps = 0;
        que.push({0, 0, k});

        while(!que.empty()){
            int size = que.size();

            while(size--){
            vector<int> curr = que.front();
            que.pop();

            int curr_i = curr[0];
            int curr_j = curr[1];
            int obs = curr[2];

            if(curr_i == m-1 && curr_j == n-1) return steps;

            for(auto& dir : directions){

                int new_i = curr_i + dir[0];
                int new_j = curr_j + dir[1];

                if(new_i >= m || new_i < 0 || new_j >= n || new_j < 0) continue;

                if(grid[new_i][new_j] == 0  && !vis[new_i][new_j][obs]){
                    que.push({new_i, new_j, obs});
                    vis[new_i][new_j][obs] = true;
                }

                else if(grid[new_i][new_j] == 1  && obs > 0 && !vis[new_i][new_j][obs-1]){
                    que.push({new_i, new_j, obs-1});
                    vis[new_i][new_j][obs-1] = true;
                }
            }
        }

        steps++;

        }
        return -1;
    }
};