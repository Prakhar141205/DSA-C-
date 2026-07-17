class Solution {
public:
    int maxDistance(vector<vector<int>>& arr) {
        
        int n = arr.size();
        int idx_min = -1;

        int m = arr.front()[0];
        int M = arr.front().back();
        int res = INT_MIN;
        for(int i=1; i<n; i++) {
            int curr_m = arr[i].front();
            int curr_M = arr[i].back();

            res = max({res, abs(M - curr_m), abs(curr_M - m)});
            m = min(m, curr_m);
            M = max(M, curr_M);
        }
        
        cout << m << " " << M ;
        return res;
    }
};