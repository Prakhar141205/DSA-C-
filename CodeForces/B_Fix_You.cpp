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
#define eb emplace_back
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, n) for (int i = 0; i < (n); i++)

void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

int main() {
    fastIO();

    int T;
    cin >> T;

    while (T--) {
        int m, n ;  cin >> m >> n ;
        vector<string> v(m) ;

        forn(i, m) {
            string s; cin >> s ;
            v[i] = s;
        }
        int cnt = 0 ;

        forn(i, n) {
            if(v[m-1][i] == 'D') cnt++;
        }
        
        forn(i, m) {
            if(v[i][n-1] == 'R') cnt++ ;
        }
        cout << cnt << "\n";
        }
       

    return 0;
}