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

        string a, b;
        cin >> a >> b;

        string ae, ao, be, bo;

        for (int i = 0; i < n; i++) {
            if (i & 1) {
                ao += a[i];
                bo += b[i];
            } else {
                ae += a[i];
                be += b[i];
            }
        }

        cout << ((ae == be && ao == bo) ? "YES" : "NO") << '\n';
    }
}