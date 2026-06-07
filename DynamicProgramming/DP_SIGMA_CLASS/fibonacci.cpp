#include <iostream>

using namespace std;

int fib(int n){
    if(n == 0) return 0;
    if (n == 1 ) return 1;

    return fib(n-1) + fib(n-2);
}


int fib(int n, vector<int>& dp){

    if(n == 0) return 0;
    if (n == 1) return 1;
    if(dp[n] != -1) return dp[n];

    return dp[n] = fib(n-1) + fib(n-2);
}

int fibTab(int n){
    vector<int> dp(n+1, 0);
    dp[1] = 1;

    for(int i=2; i<=n; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}
int main(){
    int n = 5;
    vector<int> dp(n+1, 0);
    cout << fib(n, dp) << " ";
    return 0;
}