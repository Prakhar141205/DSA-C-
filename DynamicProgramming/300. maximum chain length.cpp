class Solution {
public:
    int n;
    int t[1001][1001] ;
    int solve(vector<vector<int>>& pairs, int idx, int p) {
        if(idx >= n ) return 0;

        int take = 0;
        if(p != -1 && t[idx][p] != -1 ) return t[idx][p];

        if(p == -1 || pairs[idx][0] > pairs[p][1]) {
            take = 1 + solve(pairs, idx+1, idx) ;
        }

        int skip = solve(pairs, idx+1, p) ;
        if(p != -1 ) t[idx][p] = max(take, skip) ;
        return max(take, skip) ;
    }
    int findLongestChain(vector<vector<int>>& pairs) {
        n = pairs.size();

        sort(pairs.begin(), pairs.end()) ;
        memset(t, -1, sizeof(t)) ;

        return solve(pairs, 0, -1) ;
    }   
};