#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

void run() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        if (ans > a[i]) {
            ans += a[i];
        } else {
            ans = a[i];
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--) {
        run();
    }
    return 0;
}