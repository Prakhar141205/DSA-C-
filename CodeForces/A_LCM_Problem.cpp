#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

using vi = vector<int>;
using vll = vector<ll>;
const int INF = 1e9;
const int MOD = 1e9 + 7;

// -------------------- Fast IO --------------------
void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

// -------------------- Solve --------------------
void solve() {
    int l, r ;
    cin >> l >> r ;

    2*l <= r ? (cout << l << " " << 2*l << "\n"): (cout << -1 << " " << -1 << "\n");
}

// -------------------- Main --------------------
int main() {
    fastIO();

    int T = 1;
    cin >> T;
   
    while(T--){
        solve();
    }
    return 0;
}