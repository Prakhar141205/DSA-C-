class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {

        vector<vector<int>> res(n, vector<int> (n, 0));
        
        int t=0, r=n-1, b=n-1,l=0;
        int dir = 0;
        int cnt = 1 ;
        while(r >= l && b >= t) {

            if(dir == 0) {

                for(int i=l; i<=r; i++) {
                    res[t][i] = cnt++;
                }
                t++;
            }
            if(dir == 1) {

                for(int i=t; i<=b; i++) {
                    res[i][r] = cnt++;
                }
                r--;
            }
            if(dir == 2) {

                for(int i=r; i>=l; i--) {
                    (res[b][i]) = cnt++;;
                }
                b--;
            }
            if(dir == 3) {

                for(int i=b; i>=t; i--) {
                    (res[i][l]) = cnt++;
                }
                l++;
            }


            dir = (dir + 1) % 4 ;
        }

        return res ;
    }
};