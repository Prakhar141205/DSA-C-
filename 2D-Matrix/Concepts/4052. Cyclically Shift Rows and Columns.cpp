class Solution {
public:
    vector<vector<int>> cyclicShift(int n, vector<vector<int>>& grid, vector<int>& rs, vector<int>& cs) {
        vector<vector<int>> temp(n, vector<int> (n)) ;

        for(int i=0; i<n; i++) {

            for(int j=0; j<n; j++) {

                temp[i][j] = grid[i][(j+rs[i]) % n];
            }
        }

        for(int i=0; i<n; i++) {

            for(int j=0; j<n; j++) {

                grid[j][i] = temp[(j+cs[i])%n][i];
            }
        }

        return grid;
    }
};

// inplace solution

class Solution {
public:
    vector<vector<int>> cyclicShift(int n, vector<vector<int>>& grid, vector<int>& rs, vector<int>& cs) {
        vector<vector<int>> temp(n, vector<int> (n)) ;
         
        // rotate the row vectors as similar to the question reverse the array  k (Here k is varying each time)times
        for(int i=0; i<n; i++) {
            int k = rs[i];
            reverse(grid[i].begin(), grid[i].begin() + k);
            reverse(grid[i].begin()+k, grid[i].end());
            reverse(grid[i].begin(), grid[i].end());
        }

        // transpose so that column vector become row vector we can't access the entire column vector at once because in cpp Row major matrix is implemented

        // again rotate the row vectors as similar to the question reverse the array k(Here k is varying each time) times

        for(int i=0; i<n; i++) {
            for(int j=i+1; j<n; j++) {
                swap(grid[i][j], grid[j][i]);
            }
        }

        // again rotate the row vectors as similar to the question reverse the array k(Here k is varying each time) times

        for(int i=0; i<n; i++) {
            int k = cs[i];
            reverse(grid[i].begin(), grid[i].begin() + k);
            reverse(grid[i].begin()+k, grid[i].end());
            reverse(grid[i].begin(), grid[i].end());
        }
        // again make the row vector to the column vector
        for(int i=0; i<n; i++) {
            for(int j=i+1; j<n; j++) {
                swap(grid[i][j], grid[j][i]);
            }
        }
        // final answer in the grid itself
        
        return grid;
    }
};