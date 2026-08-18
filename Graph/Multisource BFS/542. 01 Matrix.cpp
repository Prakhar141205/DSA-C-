class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}} ;

        auto valid = [&](int& i, int& j) {
            return i >= 0 && i < m && j >= 0 && j < n ;
        };

        queue<pair<int, int>> que ;

        for(int i=0; i<m; i++) {

            for(int j=0; j<n; j++) {

                if(mat[i][j] == 0) {
                    que.push({i, j});
                }else {
                    mat[i][j] = -1 ;
                }
            }
        }

        while(!que.empty()) {
            auto [i, j] = que.front();
            que.pop();

            for(auto [x, y] : directions) {
                int nx = i + x ;
                int ny = j + y;

                if(!valid(nx, ny)) continue;

                if(mat[nx][ny] == -1) {
                    mat[nx][ny] = mat[i][j] + 1 ;
                    que.push({nx, ny});
                }
            }
        }
        
        return mat ;
    }
};