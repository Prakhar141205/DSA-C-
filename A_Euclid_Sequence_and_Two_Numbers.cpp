#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;

    while (tc--) {
        int n;
        cin >> n;

        vector<ll> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }

        if (n == 2) {
            if (v[0] < v[1]) swap(v[0], v[1]);
            cout << v[0] << " " << v[1] << "\n";
            continue;
        }

        sort(v.begin(), v.end(), greater<ll>());

        bool ok = true;

        for (int i = 0; i < n - 2; i++) {
            if (v[i] % v[i + 1] != v[i + 2]) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            cout << -1 << "\n";
        } else {
            cout << v[0] << " " << v[1] << "\n";
        }
    }

    return 0;
}