class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        int r = 0, c = n-1 ;

        while(c >= 0 && r < m) {

            if(target > matrix[r][c]) {
                r++;
            }else if(target < matrix[r][c]){
                c--;
            }else {
                return true;
            }
        }
        return false;
    }
};