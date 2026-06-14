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
    int n, k;
    cin>>n>>k;

    string s;
    cin >> s;

    int sz = s.length();
    if(sz == 1 && s[0] == '1'){
        cout << "YES\n";
    }else if(sz == 0 && s[0] == '0'){
        cout << "NO\n";
    }
    // int cnt1=0;
    // for(int i=0; i<sz; i++){
    //     if(s[i] == '1'){
    //         cnt1++;
    //     }
    // }

    // if(cnt1%2 != 0) {cout <<"NO\n"; return;}

    for(int i=0; i< n-k; i++){
        if(s[i] == '1'){
            if(s[i+k-1] != '1'){
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
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