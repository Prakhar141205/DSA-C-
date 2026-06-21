class Solution {
public:
    vector<string> createGrid(int m, int n) {
        string s = "";

        for(int i=0; i<n; i++){
            s += '#';
        }
        vector<string> grid(m, s);

        for(int i=0; i<m; i++){
            grid[i][0] = '.';
        }

        for(int i=0; i<n; i++){
            grid[m-1][i] = '.';
        }

        return grid;
    }
};

// TC = O(m*n)
// SC =light O(n*m)