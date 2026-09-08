class Solution {
public:
    int m, n;
    int t[501][501];

    int solve(vector<int>& nums1, vector<int>& nums2, int i, int j) {
        if(i >= m || j >= n) return 0;
        if(t[i][j] != -1) return t[i][j];
        if(nums1[i] == nums2[j]) {
            return t[i][j] = 1 + solve(nums1, nums2, i+1, j+1);
        }

        return t[i][j] = max(solve(nums1, nums2, i+1, j), solve(nums1, nums2, i, j+1) ) ;

    } 
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        m = nums1.size();
        n = nums2.size();
        memset(t, -1, sizeof(t));
        return solve(nums1, nums2, 0, 0);
    }
};

// Bottom up

class Solution {
public:
    int m, n;
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        m = nums1.size();
        n = nums2.size();
        vector<vector<int>> t(m+1, vector<int>(n+1, 0));

        for(int i=1; i<=m; i++) {
            for(int j=1; j<=n; j++) {
                if(nums1[i-1] == nums2[j-1]) {
                    t[i][j] = 1 + t[i-1][j-1];
                }else {
                    t[i][j] = max(t[i-1][j], t[i][j-1]);
                }
            }
        }

        return t[m][n];
    }
};
    