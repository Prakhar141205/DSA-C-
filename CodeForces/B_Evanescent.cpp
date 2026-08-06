#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        string s;
        cin >> s;

        int groups = 1;
        for (int i = 1; i < n; i++)
            if (s[i] != s[i - 1])
                groups++;

        int ans = INT_MAX;

        for (int i = 1; i < n - 1; i++) {
            int L = (s[i - 1] != s[i]);
            int R = (s[i] != s[i + 1]);
            int M = (s[i - 1] != s[i + 1]);

            ans = min(ans, groups - L - R + M);
        }

        cout << ans << '\n';
    }

    return 0;
}