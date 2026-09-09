#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;

    while(t--) {

        ll x, y, k; cin >> x >> y >> k ;

        ll d = y-x;
        ll ans = 0;
        ll cnt = min(k, max(0LL, d-x+1));

        for(ll i=0; i < cnt; i++) {
            ans += (d % (x+i));
        }

        ans += (k - cnt) * d ;


        cout << ans << "\n";
    }

    return 0;
}