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
using vpi = vector<pair<int, int>> ;

// -------------------- Constants --------------------
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;

// -------------------- Macros --------------------
#define pb push_back
#define ff first
#define ss second
#define all(x) (x.begin(), x.end())
// -------------------- Fast IO --------------------
void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}


// -------------------- Main --------------------
int main() {
    fastIO();

    int n, k ; cin >> n >> k ;

    int t = n ;
    vpi temp ;
    int ts = 0;
    int i=1;
    while(t--) {
        int x ; cin >> x ;
        temp.pb({x, i});
        ts += x ;
        i++;

    }


    if(ts <= k) {
        cout << n << "\n";
        for(int i=1; i<=n; i++) cout << i << " ";
        return 0;
    }

    sort(temp.begin(), temp.end()) ;

    // for(auto [a, b] : temp ) cout << a << " " << b  << "\n";

    int sum = 0;
    int j = 0;
    int cnt = 0;
    vi ans ;
    while(j < temp.size() && sum <= k ){

        sum += temp[j].first;

        if(sum <= k) {
            cnt++;
            ans.pb(temp[j].second) ;
        }

        j++;
    }

    cout << cnt << "\n";

    for(int& e :  ans) cout << e << " ";

    return 0;
}; 