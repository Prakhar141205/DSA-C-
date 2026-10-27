class Solution {
public:
    vector<string> createGrid(int n, int m) {
        vector<string> grid(n, string(m, '#'));
        for (int i = 0; i < m; i++)
            grid[0][i] = '.';
        for (int i = 0; i < n; i++)
            grid[i][m - 1] = '.';
        return grid;
    }
};


class Solution {
public:
    vector<string> createGrid(int m, int n) {

        vector<string> ans(m);

        for(int i=0; i<m; i++) {

            string curr = "";

            for(int j=0; j<n; j++) {

                if(i == 0) {
                    curr += '.';
                }else {
                    if(j == n-1) {
                        curr += '.';
                    }else {
                        curr += '#';
                    }
                }
            }
            
            ans[i] = curr;
        }

        return ans;
    }
};