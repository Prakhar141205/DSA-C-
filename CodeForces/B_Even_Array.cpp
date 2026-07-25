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
    int n ;
    cin >> n ;
    int even_cnt = 0;
    int odd_cnt = 0;
    int i = 0;
    int c_placed = 0;
    int ic_placed = 0;

    while(n--){
        int a;
        cin >> a ;

        if(a & 1) odd_cnt += 1;
        else even_cnt += 1 ;

        if((i & 1) && (a & 1)) {
            c_placed += 1;
        }else if(i % 2 == 0 && a & 2 == 0 ){
            c_placed += 1 ;
        }else if(i%2 == 0 && a & 1) ic_placed += 1;
        else if(i % 2 != 0 && a & 1 == 0) ic_placed += 1;

        


    }

    if(even_cnt != odd_cnt) {cout << -1 << "\n"; return ;}

    cout << ic_placed / 2 << "\n";




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