// binary Search in 2D Matrix
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        int st = 0, end = m*n-1 ;

        while(st <= end) {
            int mid = st + (end-st)/2 ;
            int r = mid/n;
            int c = mid % n ;
            if(target > matrix[r][c]) {
                st = mid + 1;
            }else if(target < matrix[r][c]){
                
                end = mid - 1;
            }else {
                return true;
            }
        }
        return false;
    }
};