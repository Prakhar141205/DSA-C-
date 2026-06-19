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
    vector<int> a(n);
    vector<int> b(n);
   
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    for(int i=0; i<n; i++){
        cin >> b[i];
    }

    int cnt=0;
    for(int i=0;  i < n; i++){
        

        for(int j=0; j < n-1; j++){
            if(a[j+1] < a[j]){
                cnt++;
                swap(a[j+1], a[j]);
            }
        }
    }

    cout << cnt << "\n";
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