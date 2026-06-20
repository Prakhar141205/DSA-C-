#include<bits/stdc++.h>

using namespace std;
int a[500000], pref[500001], suf[500001], dpvl[500001], inf = 1000000000;

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int T, n, m, i, c;
    for (cin >> T; T > 0; T--) {
        cin >> n >> m;
        for (i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
        }
        for (i = 0; i <= n; i++) {
            pref[i] = -inf;
            suf[i] = -inf;
            dpvl[i] = -inf;
        }
        pref[0] = 0;
        for (i = 0; i < n; i++) {
            c = suf[i];
            if (i - a[i] >= 0) {
                c = max(c, dpvl[i - a[i]]);
                c = max(c, pref[i - a[i]]);
            }
            c++;
            pref[i + 1] = max(pref[i], c);
            suf[i + 1] = max(suf[i + 1], suf[i]);
            if (i - a[i] >= 0)dpvl[i - a[i]] = max(dpvl[i - a[i]], c);
            if (i - a[i] + m <= n)suf[i - a[i] + m] = max(suf[i - a[i] + m], c);
        }
        cout << n - max(suf[n], 0) << '\n';
    }
    return 0;
}