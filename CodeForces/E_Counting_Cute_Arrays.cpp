#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> X(n+1);
        for (int i = 1; i <= n; i++)
            cin >> X[i];

        vector<long long> dp(n+1);
        dp[0] = 1;

        for (int i = 1; i <= n; i++) {

            vector<long long> newdp(n+1);

            if (X[i] != -1) {

                int j = X[i];

                if (j >= i) {
                    dp.assign(n+1,0);
                    break;
                }

                for (int k = 0; k <= j; k++)
                    newdp[j] = (newdp[j] + dp[k]) % MOD;

            } 
            else {

                for (int j = 0; j < i; j++) {
                    long long sum = 0;

                    for (int k = 0; k <= j; k++)
                        sum = (sum + dp[k]) % MOD;

                    newdp[j] = sum;
                }

            }

            dp = newdp;
        }

        long long ans = 0;
        for (auto v : dp)
            ans = (ans + v) % MOD;

        cout << ans << "\n";
    }
}