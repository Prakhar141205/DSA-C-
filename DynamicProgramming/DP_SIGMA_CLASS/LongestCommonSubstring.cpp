#include <string>
#include <iostream>
#include <vector>
using namespace std;

int getMaxLenSub(string s1, string s2){
    int n = s1.length();
    int m = s2.length();

    if(n == 0 || m == 0) return 0;


    if(s1[n-1] == s2[m-1]) 
        return 1 + getMaxLenSub(s1.substr(0, n-1), s2.substr(0, m-1));
    else return 0;
    
}

// Memoization

int getMaxLenSubMem(string s1, string s2, vector<vector<int>> &dp){
    int n = s1.length();
    int m = s2.length();

    if(n == 0 || m == 0) return 0;

    if(dp[n][m] != -1) return dp[n][m];

    if(s1[n-1] == s2[m-1]) return dp[n][m] = 1 + getMaxLenSubMem(s1.substr(0, n-1), s2.substr(0, m-1), dp);
    else{
        return dp[n][m] = max(getMaxLenSubMem(s1.substr(0, n-1), s2, dp), getMaxLenSubMem(s1, s2.substr(0, m-1), dp));
    }
}

int getMaxLenSubTab(string s1, string s2){
    int n = s1.length();
    int m = s2.length();

    vector<vector<int>> dp(n+1, vector<int> (m+1, 0));
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = 1 + dp[i-1][j-1];
            }else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[n][m];
}


int main(){
    string s1 = "abcde";
    string s2 = "adf";
    // vector<vector<int>> dp(s1.size()+1, vector<int> (s2.size()+1, -1));

    cout << "Max Length = "<< getMaxLenSub(s1, s2) << "\n";
    return 0;

}