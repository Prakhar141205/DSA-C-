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
using vpi = vector<pair<int, int>>;
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
// -------------------- Main --------------------
int main() {
    fastIO();

    int T = 1;
    cin >> T;
    int i=1;
    vpi v;

    while(T--){
        int x ;
        cin >> x ;
        
        v.push_back({x, i});
        i++;
        
    }

    sort(all(v));
    for(auto [x, i] : v) cout << i << " " ;
    cout << "\n";
    return 0;
}