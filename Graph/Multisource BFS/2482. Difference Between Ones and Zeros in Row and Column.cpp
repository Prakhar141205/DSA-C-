class Solution {
public:
    vector<vector<int>> onesMinusZeros(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<int> row(m, 0) ;
        vector<int> col(n, 0) ;

        for(int i=0; i<m; i++) {
            int cnt1 = 0;
            for(int j=0; j<n; j++) {

                if(grid[i][j] == 1) {
                    cnt1++;
                }
            }
            row[i] = cnt1;
        }

        for(int i=0; i<n; i++) {
            int cnt1c = 0;
            for(int j=0; j<m; j++) {
                if(grid[j][i] == 1) {
                    cnt1c++;
                }
            }
            col[i] = cnt1c;
        } 


        for(int x : row) cout << x <<  " ";
        for(int x : col) cout << x << " ";

        for(int i=0; i<m; i++ ) {

            for(int j=0; j<n; j++) {

                grid[i][j] = row[i] + col[j] - (n - row[i]) - (m - col[j]) ;
            }
        }
        return grid;
        
    }
};