#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        long long pref = 0;
        long long mn = LLONG_MAX;

        for (int i = 1; i <= n; i++) {
            long long x;
            cin >> x;

            pref += x;

            mn = min(mn, pref / i);

            cout << mn << " ";
        }

        cout << '\n';
    }
}