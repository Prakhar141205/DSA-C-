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
int cnt=0;
vi v;
void solve() {
    string s;
    cin >> s;

    vector<int> ans;
    int n = s.size();

    for (int i = 0; i < n; i++) {
        if (s[i] != '0') {
            string cur(n, '0');
            cur[i] = s[i];
            ans.push_back(stoi(cur));
        }
    }

    cout << ans.size() << "\n";
    for (int x : ans)
        cout << x << " ";
    cout << "\n";
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