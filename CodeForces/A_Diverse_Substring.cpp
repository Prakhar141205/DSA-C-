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

int main() {
    fastIO();

    int n; 
    cin >> n ;

    string s ;
    cin >> s ;

    for(int i=0; i<n-1; i++) {
        if(s[i] != s[i+1]) {
            cout << "YES\n";
            cout << s[i] << s[i+1] << "\n";
            return 0;
        }
    }

    cout << "NO\n";

    return 0;
}