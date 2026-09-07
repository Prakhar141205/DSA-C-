/*
      MY YOUTUBE VIDEO ON THIS Qn : https://www.youtube.com/watch?v=YZzJrQQP-Pk
      Company Tags                : Google, TikTok
      Leetcode Link               : https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/
*/


//Recursion - TLE
class Solution {
public:
    /*
        dp[r][c][l] =  number of ways to cut mat[r..n-1][c..m-1] into l pieces so that each piece has at least one apple on them, 
        
        g[r][c] = number of apples on mat[r..n-1][c..m-1]. 
        
        Because after cutting, we always have the down-right corner of the matrix left, so this setting is valid.
    */
    int m, n;
    int apples[55][55];
    long long MOD = 1e9 + 7;
    
    int solve(int i, int j, int k) {
        
        if(apples[i][j] < k)
            return 0;
        
        if(k == 1) {
            return (apples[i][j] >= 1) ? 1 : 0;
        }
        
        int ans = 0;
        
        for (int h = i + 1; h < m; h++) {
            
            if (apples[i][j] - apples[h][j] > 0 && apples[h][j] >= k - 1) {
                
                ans = (ans % MOD + solve(h, j, k - 1) % MOD) % MOD;
                
            }
        }

        for (int v = j + 1; v < n; v++) {
            
            if (apples[i][j] - apples[i][v] > 0 && apples[i][v] >= k - 1) {
                ans = (ans % MOD + solve(i, v, k - 1) % MOD) % MOD;
            }
        }

        return ans;
        
    }
    
    int ways(vector<string>& pizza, int k) {
        m = pizza.size();
        n = pizza[0].length();
        
        memset(apples, 0, sizeof(apples));
        
        for(int i = m-1; i>=0; i--) {
            
            for(int j = n-1; j>=0; j--) {
                
                apples[i][j] = apples[i][j+1];
                
                for(int l = i; l<m; l++) {
                    apples[i][j] += (pizza[l][j]=='A');
                }
                
            }
            
        }
        
        return solve(0, 0, k);
        
    }
};
      
//Recursion + Memoization - ACCEPTED
class Solution {
public:
    /*
        dp[i][j][k] =  number of unique ways to cut mat[i..m-1][j..n-1] into k pieces so that each piece has atleast one apple , 
        
        apples[i][j] = number of apples on mat[i..m-1][j..n-1]. 
        Because after cutting, we always have the down-right corner of the matrix left, so this setting is valid.
    */
    
    int m, n;
    int apples[55][55];
    int dp[55][55][15];
    long long MOD = 1e9 + 7;
    
    int solve(int i, int j, int k) {
        
        if(apples[i][j] < k)
            return 0;
        
        if(k == 1) {
            return (apples[i][j] >= 1) ? 1 : 0;
        }
        
         
        if(dp[i][j][k] != -1)
            return dp[i][j][k];
        
        dp[i][j][k] = 0;
        
        for (int h = i + 1; h < m; h++) {
            
            if (apples[i][j] - apples[h][j] > 0 && apples[h][j] >= k - 1) {
                
                dp[i][j][k] = (dp[i][j][k] % MOD + solve(h, j, k - 1) % MOD) % MOD;
                
            }
        }

        for (int v = j + 1; v < n; v++) {
            
            if (apples[i][j] - apples[i][v] > 0 && apples[i][v] >= k - 1) {
                dp[i][j][k] = (dp[i][j][k] % MOD + solve(i, v, k - 1) % MOD) % MOD;
            }
        }

        return dp[i][j][k];
        
    }
    
    int ways(vector<string>& pizza, int k) {
        m = pizza.size();
        n = pizza[0].length();
        
        memset(apples, 0, sizeof(apples));
        
        for(int i = m-1; i>=0; i--) {
            
            for(int j = n-1; j>=0; j--) {
                
                apples[i][j] = apples[i][j+1];
                
                for(int l = i; l<m; l++) {
                    apples[i][j] += (pizza[l][j]=='A');
                }
                
            }
            
        }
        
        memset(dp, -1, sizeof(dp));
        return solve(0, 0, k);
        
    }
};

class Solution {
public:
    const long long mod = 1e9+7 ;
    int m, n;
    int apples[55][55] ;
    int t[55][55][15];

    int solve(int i, int j, int k){
        if(apples[i][j] < k ) return 0;
        if(k == 1) return (apples[i][j] >= 1) ? 1 : 0  ;

        if(t[i][j][k] != -1 )  return t[i][j][k] ;
        t[i][j][k] = 0;
        // horizontal cut

        for(int h=i+1; h<m; h++) {

            int lowerSliceApples = apples[h][j];
            int UpperSliceApples = apples[i][j] - lowerSliceApples ;

            if(UpperSliceApples >= 1 && lowerSliceApples >= k-1) {
                t[i][j][k] = (t[i][j][k] % mod + solve(h, j, k-1) % mod) % mod ;
            }
        }

        // Vertical Cut

        for(int v=j+1; v < n; v++) {

            int rightSliceApples = apples[i][v] ;
            int leftSliceApples = apples[i][j] - rightSliceApples ;

            if(leftSliceApples >= 1 && rightSliceApples >= k-1) {

                t[i][j][k] = (t[i][j][k] % mod + solve(i, v, k-1) % mod) % mod ;
            }
        }

        return t[i][j][k] ;
    }
    int ways(vector<string>& pizza, int k) {
        m = pizza.size();
        n = pizza[0].length();
        memset(apples, 0, sizeof(apples)) ;
        // make apples array
        // apples[i][j] ==> Number of apples in pizza from apples[i][j] to apples[m-1][n-1]
        for(int i = m-1; i>=0; i--) {

            for(int j=n-1; j >=0; j--) {

                apples[i][j] = apples[i][j+1];

                for(int l=i; l<m; l++) {

                    if(pizza[l][j] == 'A') {
                        apples[i][j]++;
                    }
                }
            }
        }

        memset(t, -1, sizeof(t));
        return solve(0, 0, k);
        
    }
};