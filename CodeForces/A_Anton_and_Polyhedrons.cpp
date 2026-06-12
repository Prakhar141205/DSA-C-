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
int sum=0;
void solve() {
    
    string s;
    cin >> s;

    if(s == "Tetrahedron") sum += 4;
    else if(s == "Cube") sum += 6;
    else if(s == "Octahedron") sum += 8;
    else if(s == "Dodecahedron") sum += 12;
    else if(s == "Icosahedron") sum += 20;

    
}

// -------------------- Main --------------------
int main() {
    fastIO();

    int T = 1;
    cin >> T;
    
    while(T--){
        solve();
    }

    cout << sum << "\n";
    return 0;
}