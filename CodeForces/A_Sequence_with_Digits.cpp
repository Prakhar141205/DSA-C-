// #include <bits/stdc++.h>
// using namespace std;

// // -------------------- Typedefs --------------------
// using ll = long long;
// using ull = unsigned long long;
// using ld = long double;

// using pii = pair<int, int>;
// using pll = pair<ll, ll>;

// using vi = vector<int>;
// using vll = vector<ll>;

// // -------------------- Constants --------------------
// const int INF = 1e9;
// const ll LINF = 1e18;
// const int MOD = 1e9 + 7;

// // -------------------- Macros --------------------
// #define pb push_back
// #define ff first
// #define ss second
// #define all(x) (x).begin(), (x).end()
// #define rall(x) (x).rbegin(), (x).rend()

// // -------------------- Fast IO --------------------
// void fastIO() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
// }

// // -------------------- Solve --------------------
// int getMin(ll n){
//     int m =  9;
//     while(n>0){
//         m = min(m, (int) n%10);
//         n/=10;
//     }
//     return m;
// }

// int getMax(ll n){
//     int m =  0;
//     while(n>0){
//         m = max(m, (int)n%10);
//         n/=10;
//     }
//     return m;
// }


// void solve() {
//     ll n, k;
//     cin >> n >> k;


//     while(k>1){
//         n += (ll)getMin(n)*getMax(n);
//         k--;
//     }

//     cout << n << "\n";
// }

// // -------------------- Main --------------------
// int main() {
//     fastIO();

//     int T = 1;
//     cin >> T;
   
//     while(T--){
//         solve();
//     }
//     return 0;
// }



// ----------------------Method 2 ----------------------------

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

int getMin(string s){
    auto it = min_element(s.begin(), s.end());

    return (int)*it - '0';
}

int getMax(string s){
    auto it = max_element(s.begin(), s.end());

    return (int)*it - '0';
}
void solve() {
    long long n, k;
    cin >> n >> k;

    while (k > 1) {
        string s = to_string(n);

        int mn = getMin(s);
        int mx = getMax(s);

        if (mn == 0) break;

        n += 1LL * mn * mx;
        k--;
    }

    cout << n << "\n";
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