class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        vector<bool> dp(n, false);
        dp[0] = true;

        int count = 0;

        for (int i = 1; i < n; i++) {
            if (i - minJump >= 0 && dp[i - minJump]) count++;
            if (i - maxJump - 1 >= 0 && dp[i - maxJump - 1]) count--;

            dp[i] = (s[i] == '0' && count > 0);
        }

        return dp[n - 1];
    }
};


class Solution {
public:
    bool canReach(string s, int m, int M) {
        int n = s.length();
        if(s[n-1] == '1') return false;

        vector<int> dp(n, 0);
        vector<int> pre(n, 0);

        dp[0]=1;
        pre[0]=1;

        for(int i=1; i<n; i++){
            int l = max(0, i-M); // M => maxJump
            int r = i - m;

            if(s[i] == '0' && r >= 0){
                int sum = pre[r] - (l > 0 ? pre[l-1] : 0);
                if(sum > 0) dp[i] = 1;

            }

            pre[i] = pre[i-1] + dp[i];
        }

        return dp[n-1] == 1;
    }
};