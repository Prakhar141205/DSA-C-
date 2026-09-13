/*
For finding overlapping between 2 matrices 
row offset is -n+1 to n-1 inclusive similarly columns
    A[i][j] = B[i+rowoffset][j+offset] 
    // contingent to the indices used inside matrices are valid
    
*/
class Solution {
public:
    int n;
    int cntMaxOverLaps(vector<vector<int>>& img1, vector<vector<int>>& img2, int ro, int co) {

        int cnt = 0;
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {

                int b_i = ro + i;
                int b_j = co + j ;

                if(b_i < 0 || b_i >= n || b_j < 0 || b_j >= n) continue;

                cnt += (img1[i][j] == 1 && img2[b_i][b_j] == 1);
            }
        }
        return cnt;
    }
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        n = img1.size();
        int ans = 0;

        for(int ro = -n+1; ro < n; ro++) {

            for(int co = -n+1; co < n; co++) {

                int cnt = cntMaxOverLaps(img1, img2, ro, co);
                ans = max(ans, cnt);
            }
        }

        return ans;
    }
};