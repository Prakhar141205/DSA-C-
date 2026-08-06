// since in this question all edges has same weight we can use queue inplace of Priority queue

class Solution {
public:
   vector<vector<int>> directions = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}} ;
    typedef pair<int, pair<int, int>> P ;
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size() ;
        if(grid[0][0] == 1 || grid[m-1][n-1] == 1)
                return -1;
        auto isSafe = [&] (int x, int y) {
            return x >= 0 && y >= 0 && x < m && y < n ;
        };
        vector<vector<int>> result(m, vector<int> (n, INT_MAX));

        priority_queue<P, vector<P>, greater<P>> pq ;

        result[0][0] = 0;
        pq.push({0, {0, 0 }}) ; // dist, i, j

        while(!pq.empty()) {
            int d = pq.top().first ;
            pair<int, int> node = pq.top().second ;

            int x = node.first;
            int y = node.second;

            pq.pop();

            for(auto dir : directions) {
                int x_ = x + dir[0];
                int y_ = y + dir[1];

                int dist = 1 ;

                if(isSafe(x_, y_) && grid[x_][y_] == 0 && d + dist < result[x_][y_]) {
                    // no need of marking visited because when we again come to visited node its distance will always more than than it automatically not pushed inside the queue;
                    result[x_][y_] = d + dist ;
                    pq.push({d + dist, {x_, y_}});

                } 
            }
        }


        if(result[m-1][n-1] == INT_MAX) return -1 ;

        return result[m-1][n-1]+1 ; 
    }
};