#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

using vi = vector<int>;
using vll = vector<ll>;
using vpii = vector<pii>;
using vpll = vector<pll>;

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;

#define pb push_back
#define forn(i, n) for (int i = 0; i < (n); i++)

void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

ll solve(string& s, int idx, int tight, int cnt) {
    if(idx == s.length()) return 0;

    ll res = 0;

    int lb = 0;
    int up = (tight == 1) ? s[idx]-'0' : 9 ;

    for(int dig = lb; dig <= up; dig++) {
        int updateCnt = (dig != 0 ? 1 : 0) ;
        if(updateCnt <= 3) {
            res += solve(s, idx+1, (tight & (dig == s[idx] - '0')), updateCnt);
        }
    }

    return res;p
}
int main() {
    fastIO();

    int n; cin >> n;
    while(n--) {
        ll l, r ;
        cin >> l >> r ;
        string ls = to_string(l);
        string rs = to_string(s);

        cout << solve(r, 0, 1, 0) - solve(l-1, 0, 1, 0) ;
    }
    return 0;
}