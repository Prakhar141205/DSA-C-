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
    int n;
    cin >> n;

    vector<int> v;
    int sum=0;

    while(n--){
        int x;
        cin >> x;
        v.pb(x);
    }

    for(int i=0; i<v.size(); i++) {
        
        for(int j=i+1; j<v.size(); j++){

            if(v[j] > v[i]){
                v[j] = v[i];
                break;
            }
        }
    }

    for(int x : v) {sum += x;}

    cout << sum << "\n";
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