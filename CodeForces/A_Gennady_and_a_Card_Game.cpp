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
    
}

// -------------------- Main --------------------
int main() {
    fastIO();

    string s; cin >> s ;

    char c1 = s[0];
    char c2 = s[1];

    for(int i=0; i<5; i++) {
        string x ; cin >> x ;

        if(x[0] == c1 || x[1] == c2) {cout << "YES\n"; return 0;}
         
        
    }

    cout << "NO\n";
    return 0;
}