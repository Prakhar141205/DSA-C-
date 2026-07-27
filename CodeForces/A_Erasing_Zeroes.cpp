#include <bits/stdc++.h>
using namespace std;

// -------------------- Typedefs --------------------
using ll = long long;
using ull = unsigned long long;
using ld = long double;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

using vi = vector<int>;
using vll = vector<ll>;

// -------------------- Constants --------------------
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;
#define forn(i, n) for(int i=0; i<n; i++) 
// -------------------- Macros --------------------
#define pb push_back
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

// -------------------- Fast IO --------------------
void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

// -------------------- Solve --------------------
void solve() {
    string s ; cin >> s ;
    int n = s.length();

    int i_st = -1 ;

    forn(i, n) {
        if(s[i] == '1') {
            i_st = i;
            break;
        }
    }

    // if there is no 1 in the string 
    if(i_st == -1 ) {cout << 0 << "\n"; return;}


    int end_i = -1;
    for(int i=n-1; i>=0; i--) {
        if(s[i] == '1') {
            end_i = i;
            break;
        }
    }
    
    int ans =0;
    for(int i = i_st; i<= end_i; i++) {
        if(s[i] == '0') ans += 1; 
    }

    cout << ans << "\n";
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