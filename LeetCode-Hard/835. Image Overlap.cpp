class Solution {
public:
    int countOverlaps(vector<vector<int>> A, vector<vector<int>> B, int rowOff, int colOff) {
        int n = A.size();
        int cnt=0;
        for(int i=0; i<n; i++){

            for(int j=0; j<n; j++){

                /*
                A[i][j] ==> B[i+rowOff][j + colOff]
                */

                int B_i = i + rowOff;
                int B_j = j + colOff;

                if(B_i < 0 || B_i >= n || B_j < 0 || B_j >= n) continue;

                if(A[i][j] == 1 && B[B_i][B_j] == 1) cnt++;


            }
        }
        return cnt;
    }
    int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B) {
        int n = A.size();

        int maxOverlaps = 0;

        for(int rowOff = -n+1; rowOff <= n-1; rowOff++){

            for(int colOff = -n+1; colOff <= n-1; colOff++){
                int count = countOverlaps(A, B, rowOff, colOff);
                maxOverlaps = max(maxOverlaps, count);
            }
        }
        return maxOverlaps;

    }
};