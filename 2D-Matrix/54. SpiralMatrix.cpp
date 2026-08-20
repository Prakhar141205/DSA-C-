class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> res ;
        int t=0, r=n-1, b=m-1,l=0;
        int dir = 0;

        while(r >= l && b >= t) {

            if(dir == 0) {

                for(int i=l; i<=r; i++) {
                    res.push_back(matrix[t][i]);
                }
                t++;
            }
            if(dir == 1) {

                for(int i=t; i<=b; i++) {
                    res.push_back(matrix[i][r]);
                }
                r--;
            }
            if(dir == 2) {

                for(int i=r; i>=l; i--) {
                    res.push_back(matrix[b][i]);
                }
                b--;
            }
            if(dir == 3) {

                for(int i=b; i>=t; i--) {
                    res.push_back(matrix[i][l]);
                }
                l++;
            }


            dir = (dir + 1) % 4 ;
        }

        return res ;
    }
};