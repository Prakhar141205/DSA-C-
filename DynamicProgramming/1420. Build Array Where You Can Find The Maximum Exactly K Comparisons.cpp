class Solution {
public:
    const int mod = 1e9 + 7 ;
    int M, N, K ;
    int t[51][51][101] ;

    int solve(int idx, int search_cost, int maxVal) {
        if(idx == N) {
            if(search_cost == K) return 1 ;
            else return 0 ;
        }

        if(maxVal != -1 && t[idx][search_cost][maxVal] != -1 ) return t[idx][search_cost][maxVal] ;
        int res = 0;

        for(int i=1; i<=M; i++) {
            if(i > maxVal) {
                res = (res + solve(idx+1, search_cost+1, i))% mod ;
            }else {
                res = (res + solve(idx+1, search_cost, maxVal))% mod ;
            }
        }
        if(maxVal != -1) t[idx][search_cost][maxVal] = res % mod ;
        return res % mod ;
    }
    int numOfArrays(int n, int m, int k) {
        M = m, N = n, K = k ;
        memset(t, -1, sizeof(t)) ;

        return solve(0, 0, -1) ;    
    }
};