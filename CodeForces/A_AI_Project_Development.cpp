#include <bits/stdc++.h>
using namespace std;

long long ceil_div(long long a, long long b) {
    return (a + b - 1) / b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long n, x, y, z;
        cin >> n >> x >> y >> z;

        // Option 1: no AI
        long long ans1 = ceil_div(n, x + y);

        // Option 2: use AI
        long long finish_by_maxim = ceil_div(n, x);
        long long ans2;

        if (finish_by_maxim <= z) {
            ans2 = finish_by_maxim;
        } else {
            long long remaining = n - x * z;
            ans2 = z + ceil_div(remaining, x + 10 * y);
        }

        cout << min(ans1, ans2) << '\n';
    }

    return 0;
}