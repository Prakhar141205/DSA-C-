class Solution {
public:
    vector<pair<int, int>> directions = {{-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}};
    vector<vector<vector<double>>> t ;

    Solution() {
        t = vector<vector<vector<double>>> (26, vector<vector<double>> (26, vector<double> (101, -1.0)));
    }
    double func(int n, int k, int r, int c) {
        if(r < 0 || r >= n || c < 0 || c >= n) return 0.0;

        if(k == 0) return 1.0 ;
        if(t[r][c][k] != -1) return t[r][c][k];

        double proba = 0.0;
        for(auto [x, y] : directions) {
            int nr = r + x ;
            int nc = c + y ;
            proba += func(n, k-1, nr, nc) / 8.0 ;
        }

        return t[r][c][k] = proba ;
    }
    double knightProbability(int n, int k, int row, int column) {
        
        return func(n, k, row, column);
    }
};

// Tabulation Bottom up
class Solution {
public:
    
    
    double knightProbability(int n, int k, int row, int column) {
        vector<int> di = {-1, -2, -2, -1, 1, 2, 2, 1};
        vector<int> dj = {-2, -1, 1, 2, -2, -1, 1, 2};
        vector<vector<vector<double>>> dp(
            k + 1,
            vector<vector<double>>(
                n,
                vector<double>(n, 0.0)
            )
        );

        // Base case:
        // With 0 moves remaining,
        // every valid cell has probability 1.
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                dp[0][i][j] = 1.0;
            }
        }

        // Build DP layer by layer
        for(int step = 1; step <= k; step++) {

            for(int row = 0; row < n; row++) {

                for(int col = 0; col < n; col++) {

                    double probability = 0.0;

                    // Try all 8 knight moves
                    for(int move = 0; move < 8; move++) {

                        int nr = row + di[move];
                        int nc = col + dj[move];

                        if(nr < 0 || nr >= n ||
                           nc < 0 || nc >= n)
                            continue;

                        probability += dp[step - 1][nr][nc] / 8.0;
                    }

                    dp[step][row][col] = probability;
                }
            }
        }

        return dp[k][row][column];
    }
};