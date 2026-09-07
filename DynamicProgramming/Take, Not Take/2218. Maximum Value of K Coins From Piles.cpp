class Solution {
public:
    int n ;
    int t[1001][2001] ;

    int solve(vector<vector<int>>& piles, int i, int k ) {
        if(i >= n) return 0;

        if(t[i][k] != -1) return t[i][k];
        int not_taken = solve(piles, i+1, k);

        int sum = 0 ;
        int taken = 0 ;
        for(int j=0; j < min(k, (int)piles[i].size()); j++) {

            sum += piles[i][j];

            taken = max(taken, sum + solve(piles, i+1, k - (j + 1))) ;
        }

        return t[i][k] = max(taken, not_taken ) ;
    }
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        n = piles.size();
        memset(t, -1, sizeof(t));
        return solve(piles, 0, k) ;
    }
};


class Solution {
public:
    int n ;

    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        n = piles.size();
        vector<vector<int>> t(n+1, vector<int> (k+1, 0)) ;

        // t[i][j] max val when we have i piles and we can take j coins

        for(int i=1; i<=n; i++) {

            for(int coins = 0; coins <= k; coins++) {
                int sum = 0;
                for(int currCoins = 0; currCoins <= min(coins, (int)piles[i-1].size()); currCoins++) {

                    if(currCoins > 0) sum += piles[i-1][currCoins-1];

                    t[i][coins] = max(t[i][coins], sum + t[i-1][max(0, coins - currCoins)]);
                }
            }
        }
        return t[n][k] ;
    }
};