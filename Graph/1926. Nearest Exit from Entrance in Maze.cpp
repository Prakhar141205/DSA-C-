class Solution {
public:
    vector<vector<int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // down, up, right, left
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int m = maze.size();
        int n = maze[0].size();

        int r = entrance[0];
        int c = entrance[1];

        int cnt = 0;

        queue<pair<int, int>> que;
        que.push({r, c});
        maze[r][c] = '+';

        while(!que.empty()) {
            int N = que.size();

            while(N--) {
                // cannnot use ampersand here because we are poping the address just immediately hence it acts as a dangling pointer
                auto [row, col] = que.front();
                que.pop();

                if(!(row == r && col == c) && (row == 0 || col == 0 || row == m-1 || col == n-1)) return cnt;

                for(auto& d : dir) {
                    int new_x = row + d[0];
                    int new_y = col + d[1];

                    if(new_x < m && new_x >= 0 && new_y < n && new_y >=0 && maze[new_x][new_y] != '+') {
                        que.push({new_x, new_y});
                        maze[new_x][new_y] = '+';
                    }
                }
            }

            cnt++;
        }
         return -1;
        
    }
};