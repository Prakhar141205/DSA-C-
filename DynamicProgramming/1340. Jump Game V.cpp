// DP memoization
class Solution {
public:
    vector<int> dp;
    int n;

    int dfs(vector<int> arr, int d, int i){
        if(dp[i] != 0) return dp[i];
        
        int maxJumpsFromHere = 1;

        // right calls 
        for(int j=i+1; j<= min(i+d, n-1); j++){
            if(arr[j] >= arr[i]) break;
            maxJumpsFromHere = max(maxJumpsFromHere, 1+ dfs(arr, d, j));
        }

        // left calls 
        for(int j=i-1; j>= max(i-d, 0); j--){
            if(arr[j] >= arr[i]) break;
            maxJumpsFromHere = max(maxJumpsFromHere, 1+dfs(arr, d, j));
        }

        dp[i] = maxJumpsFromHere;

        return dp[i];
    }



    int maxJumps(vector<int>& arr, int d) {
        n = arr.size();
        dp.resize(n, 0);
        
        int globalMax = 0;

        for(int i=0; i<n; i++){
            globalMax = max(globalMax, dfs(arr, d, i));
        }
        return globalMax;
    }
};


class Solution {
public:
    vector<int> dp;
    int n;

    int maxJumps(vector<int>& arr, int d) {
        n = arr.size();
        dp.resize(n, 0);

        for(int i=0; i<n; i++) dp[i]=1;
        vector<int> indices(n);

        for(int i=0; i<n; i++) indices[i]=i;

        sort(indices.begin(), indices.end(), [&](int a, int b) { return arr[a] < arr[b];});
        
        int globalMax = 1;

        for(int i : indices){

            for(int j=i+1; j<= min(i+d, n-1); j++){
            if(arr[j] >= arr[i]) break;
            dp[i] = max(dp[i], 1+ dp[j]);

        }
            for(int j=i-1; j>= max(i-d, 0); j--){
            if(arr[j] >= arr[i]) break;
            dp[i] = max(dp[i], 1+ dp[j]);
        }
        globalMax =  max(globalMax, dp[i]);
    }
    
        return globalMax;
    }
};`