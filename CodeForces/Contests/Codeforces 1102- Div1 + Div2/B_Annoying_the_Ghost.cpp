#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n), c(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        set<int> s;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            s.insert(x);
        }
        bool y = true;
        for (int i = 0; i < n; ++i) {
            auto it = s.lower_bound(a[i]);
            if (it == s.end()) {
                y = false;
                break;
            }
            c[i] = *it;
            s.erase(it);
        }
        if (!y) {
            cout << -1 << '\n';
            continue;
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (c[i] > c[j]) {
                    ans++;
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
