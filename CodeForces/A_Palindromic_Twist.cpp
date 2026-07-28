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
    int n ; cin >> n ;

    while(n--) {
        int x; cin>>x;

        string s ; cin >> s ;
        bool isPali = true;
        int i=0, j=x-1;
        while(i < j) {
            
                if(abs(s[i] - s[j]) == 2 || abs(s[i] - s[j]) == 0 ) {
                    i++; j--;
                }else {
                    
                    isPali = false;
                    break;
                }

        }
        if(isPali) cout << "YES\n" ;
        else cout << "NO\n";
        
    }

    
    return 0;
}