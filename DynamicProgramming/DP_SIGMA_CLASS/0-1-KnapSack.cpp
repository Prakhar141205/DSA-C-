#include <iostream>
#include <vector>

using namespace std;

// knapsack using plane recursion
int maxProfit0-1KnapSack(vector<int> val, vector<int> wt, int W, int n){
    if(n <= 0 || W <= 0) return 0;
    int itemWt = wt[n-1];
    int itemVal = val[n-1];
    if(itemWt <= W){
        int ans1 = itemVal + maxProfit0-1KnapSack(val, wt, W-itemWt, n-1);
        int ans2 = maxProfit0-1KnapSack(val, wt, W, n-1);
        return max(ans2, ans1);
    }else{
        return maxProfit0-1KnapSack(val, wt, W, n-1);
    }
}
// knapsack memoization
int maxProfit0-1KnapSackMem(vector<int> val, vector<int> wt, int W, int n, vector<vector<int, int >> &dp){

    if(n <= 0 || W <= 0) return 0;
    if(dp[n][W] != -1) return dp[n][W];

    int itemWt = wt[n-1];
    int itemVal = val[n-1];
    if(itemWt <= W){
        int ans1 = itemVal + maxProfit0-1KnapSack(val, wt, W-itemWt, n-1);
        int ans2 = maxProfit0-1KnapSack(val, wt, W, n-1);
        return dp[n][W] = max(ans2, ans1);
    }else{
        return dp[n][W] = maxProfit0-1KnapSack(val, wt, W, n-1);
    }
    

}
// knapsack tabulation
int maxProfit0-1KnapSackTab(vector<int> val, vector<int> wt, int W, int n){

    vector<vector<int, int >> dp(n+1, vector<int> (W+1), 0);
    
    for(int i=0; i<=n; i++){
        for(int j=0; j<=W; j++){
            if(j >= wt[i]){
                int ans1 = val[i] + dp[i-1][j-wt[i]];
                int ans2 =  dp[i-1][j];
                dp[i][j] = max(ans1, ans2);
            }else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }

}


int main(){
    int n = 5;
    int W = 7;
    vector<int> val = {};
    vector<int> val = {};

    
    maxProfit0-1KnapSackMem(val, wt, W, n, dp);

    return 0;
}
