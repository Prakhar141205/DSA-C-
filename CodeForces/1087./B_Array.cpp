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

void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

int main() {
    fastIO();

    ll  n;
    cin >> n ;

    while(n--) {
        ll x ; cin >> x ;
        vi a(x) ;

        for(auto& ai : a) {
            cin >> ai ;
        }

        for(ll i = 0; i < x; i++) {
            ll p=0, n = 0;

            for(ll j= i+1; j<x; j++) {
                if(a[j] > a[i]) {
                    p++;
                }

                if(a[j] < a[i]) {
                    n++;
                }
            }

        cout << max(p, n) << " \n"[i+1 == x] ;  
        }
        
    }
    return 0;
}