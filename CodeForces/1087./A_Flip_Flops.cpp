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
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()


void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

int main() {
    fastIO();

    int T = 1 ; cin >> T  ;

    while(T--) {
        ll n, k, c ;
        cin >> n >> c >> k ;

        vi a(n) ;

        for(auto& x : a) {
            cin >> x ;
        }

        sort(all(a)) ;

        for(auto& ai : a) {
            if(ai > c) break;

            ll inc = min(k, c - ai) ;

            ai += inc ;
            k -= inc ;

            c += ai ;
        }

        cout << c << "\n";

    }
    return 0;
}