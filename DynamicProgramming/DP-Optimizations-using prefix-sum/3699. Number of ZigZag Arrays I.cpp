typedef long long ll;
const int mod = 1e9 + 7;
class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
            // vector<vector<vector<long long>>> dp(
            //     l + 1,
            //     vector<vector<long long>>(
            //         r + 1,
            //         vector<long long>(2, -1)
            //     )
            // ); 

        // rather than going from l to r we will go 1 to m
        ll m = r - l + 1 ;

        if(n == 1) return m % mod;

        vector<ll> up(m+1, 0);
        vector<ll> down(m+1, 0);

        for(int v=1; v<=m; v++){
                up[v] = v-1;
                down[v] = m - v;
        }

        for(int len=3; len<=n; len++){
            vector<ll> newUp(m+1, 0);
            vector<ll> newDown(m+1, 0);

            ll pref = 0;
            for(int v=1; v <= m; v++){
                newUp[v] = pref;
                pref = (pref + down[v])%mod;
            }

            ll suff = 0;
            for(int v=m; v >= 1; v--){
                newDown[v] = suff;
                suff = (suff + up[v])%mod;
            }

            up = newUp;
            down = newDown;
        }

        ll ans=0;

        for(int v=1; v <= m; v++){
            ans = (ans + up[v] + down[v])%mod;
        }

        return ans;

    }
};

class Solution {
public:
    const int mod = 1e9 + 7;
    int zigZagArrays(int n, int l, int r) {
        r = r - l + 1;
        vector<long long> dp(r, 0);
        iota(dp.begin(), dp.end(), 0);
        for (int i = 2; i < n; ++i) {
            long long pre = 0, cur = 0;
            if (i % 2 == 0) {
                for (int j = r - 1; j >= 0; --j) {
                    cur = (pre + dp[j]) % mod;
                    dp[j] = pre;
                    pre = cur;
                }
            } else {
                for (int j = 0; j < r; ++j) {
                    cur = (pre + dp[j]) % mod;
                    dp[j] = pre;
                    pre = cur;
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i < r; ++i) {
            ans = (ans + dp[i]) % mod;
        }
        return ans * 2 % mod;
    }
};