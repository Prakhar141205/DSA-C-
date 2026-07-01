class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        
        // leave first row and colummn and start comparing diagonally
        for(int i=1; i<n; i++){

            for(int j=1; j<m; j++){

                if(mat[i][j] != mat[i-1][j-1]) return false;
            }
        }
        return true;
    }
};