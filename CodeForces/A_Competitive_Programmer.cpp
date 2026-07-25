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
    string sn ;
    cin >> sn ;
    // string sn = to_string(n);
    bool z = false;
    int e = 0;
    int s = 0;
    for(char& c : sn) {
        if(c == '0') {
            z = true;
        }

        int d = (c-'0') ;

        if(d % 2 == 0 ) e++;

        s += d ;
    }
    
    bool isDiv = (s % 3 == 0) ? true : false;
    
    // cout << z << " " << e << " " << isDiv << "\n";

    if(z && (e >= 2) && isDiv) cout << "red" << "\n";
    else cout << "cyan" <<"\n";
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