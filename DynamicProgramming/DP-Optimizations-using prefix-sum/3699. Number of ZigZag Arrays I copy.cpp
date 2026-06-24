typedef long long ll;
const int mod = 1e9 + 7;
class Solution {
public:
    int N;
    int M;
    int dp[2001][2001][2];
    int solve(int index, int prev, bool isIncreasing) {
        if(index == N) return 1;

        if(dp[index][prev][isIncreasing] != -1) return dp[index][prev][isIncreasing];
        ll result = 0;
        if(isIncreasing) {
            for(int nextVal = prev+1; nextVal <= M; nextVal++) {
                result = (result + solve(index+1, nextVal, false))% mod;
            }
        }
        else {
            for(int nextVal = 1; nextVal <= prev-1; nextVal++) {
                result = result + solve(index+1, nextVal, true);
            }
        }

        return dp[index][prev][isIncreasing] = result;
    }
    int zigZagArrays(int n, int l, int r) {
        N = n;
        M = r - l + 1 ;
        memset(dp, -1, sizeof(dp));

        ll result = 0;

        for(int startVal=1; startVal <= M; startVal++) {

            result = (result + solve(1, startVal, true))%mod; // for increasing

            result = (result  + solve(1, startVal, false))% mod;
        }
         
         return (int)result%mod;

    }
};

// bottom up => Tanulations

typedef long long ll;
const int mod = 1e9 + 7;
class Solution {
public:
    int N;
    int M;
    int dp[2001][2001][2];
    // int solve(int index, int prev, bool isIncreasing) {
    //     if(index == N) return 1;

    //     if(dp[index][prev][isIncreasing] != -1) return dp[index][prev][isIncreasing];
    //     ll result = 0;
    //     if(isIncreasing) {
    //         for(int nextVal = prev+1; nextVal <= M; nextVal++) {
    //             result = (result + solve(index+1, nextVal, false))% mod;
    //         }
    //     }
    //     else {
    //         for(int nextVal = 1; nextVal <= prev-1; nextVal++) {
    //             result = result + solve(index+1, nextVal, true);
    //         }
    //     }

    //     return dp[index][prev][isIncreasing] = result;
    // }
    int zigZagArrays(int n, int l, int r) {
        N = n;
        M = r - l + 1 ;
        memset(dp, 0, sizeof(dp));


        // base case
        // agar last Index hai toh answer 1 hi hoga irrespective of preVal and isIncreasing
        for(int prevVal = 1; prevVal <= M; prevVal++) {
            dp[N][prevVal][1] = 1;
            dp[N][prevVal][0] = 1;
        }

        ll result = 0;

        for(int index = N-1; index>=0; index--){

            for(int prevVal = 1; prevVal <= M; prevVal++){

                // increasing 

                for(int nextVal = prevVal+1; nextVal <= M; nextVal++){
                    dp[index][prevVal][1] = (dp[index][prevVal][1] + dp[index+1][nextVal][0])%mod;
                    
                }
                // decreasing
                for(int nextVal = 1; nextVal <= prevVal-1; nextVal++){
                    dp[index][prevVal][0] = (dp[index][prevVal][0] + dp[index+1][nextVal][1])%mod;
                }

            }
        }
         
        for(int startVal = 1; startVal <= M; startVal++){
            // increasing 
            result = (result + dp[1][startVal][1])%mod;
            result = (result + dp[1][startVal][0])%mod;
        }
        
        return (int)result%mod;

    }
};


typedef long long ll;
const int mod = 1e9 + 7;
class Solution {
public:
    int N;
    int M;
    int dp[2001][2001][2];
    // int solve(int index, int prev, bool isIncreasing) {
    //     if(index == N) return 1;

    //     if(dp[index][prev][isIncreasing] != -1) return dp[index][prev][isIncreasing];
    //     ll result = 0;
    //     if(isIncreasing) {
    //         for(int nextVal = prev+1; nextVal <= M; nextVal++) {
    //             result = (result + solve(index+1, nextVal, false))% mod;
    //         }
    //     }
    //     else {
    //         for(int nextVal = 1; nextVal <= prev-1; nextVal++) {
    //             result = result + solve(index+1, nextVal, true);
    //         }
    //     }

    //     return dp[index][prev][isIncreasing] = result;
    // }
    int zigZagArrays(int n, int l, int r) {
        N = n;
        M = r - l + 1 ;
        // memset(dp, 0, sizeof(dp));


        // base case
        // agar last Index hai toh answer 1 hi hoga irrespective of preVal and isIncreasing
        for(int prevVal = 1; prevVal <= M; prevVal++) {
            dp[N][prevVal][1] = 1;
            dp[N][prevVal][0] = 1;
        }

        ll result = 0;

        for(int index = N-1; index>=0; index--){

            vector<ll> cumSumInc(M+1, 0);
            vector<ll> cumSumDec(M+1, 0);

            for(int val=1; val <= M; val++){
                cumSumInc[val] = (cumSumInc[val-1] + dp[index+1][val][1])%mod;
                cumSumDec[val] = (cumSumDec[val-1] + dp[index+1][val][0])%mod;
            }

            for(int prevVal = 1; prevVal <= M; prevVal++){

                // increasing 

                // for(int nextVal = prevVal+1; nextVal <= M; nextVal++){
                //     dp[index][prevVal][1] = (dp[index][prevVal][1] + dp[index+1][nextVal][0])%mod;
                    
                // }
                dp[index][prevVal][1] = (cumSumDec[M] - cumSumDec[prevVal] + mod)%mod;
                // decreasing
                // for(int nextVal = 1; nextVal <= prevVal-1; nextVal++){
                //     dp[index][prevVal][0] = (dp[index][prevVal][0] + dp[index+1][nextVal][1])%mod;
                // }
                dp[index][prevVal][0] = cumSumInc[prevVal-1]%mod;
            }
        }
         
        for(int startVal = 1; startVal <= M; startVal++){
            // increasing 
            result = (result + dp[1][startVal][1])%mod;
            result = (result + dp[1][startVal][0])%mod;
        }
        
        return (int)result%mod;

    }
};

