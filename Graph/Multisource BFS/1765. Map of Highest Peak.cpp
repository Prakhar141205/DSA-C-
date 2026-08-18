class Solution {
public:
     int m, n ;
     vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}} ;
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        queue<pair<int, int>> que;
        
        m = isWater.size();
        n = isWater[0].size();

        auto isValid = [&](int i, int j) {
            return i >= 0 && i < m && j >= 0 && j < n ;
        };
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {

                if(isWater[i][j] == 1) {
                    que.push({i, j});
                    isWater[i][j] = 0 ;
                }else {
                    isWater[i][j] = -1 ;
                }
            }
        }
        int z = 1;
        while(!que.empty()) {
            int t = que.size();

            while(t--) {
                auto [i, j] = que.front();

                que.pop();


                for(auto [x, y] : directions) {
                    int nx = i + x ;
                    int ny = j + y ;

                    if(!isValid(nx, ny)) continue;

                    if(isWater[nx][ny] == -1) {
                        isWater[nx][ny] = z;
                        que.push({nx, ny});
                    }
                }
            }
            z += 1 ;
        }

        return isWater ;
    }
};