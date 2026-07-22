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

// -------------------- Main --------------------
vector<vector<int>> dir = {{0, 1}, {1, 0}};
int main() {
    fastIO();

    ll m, n, k ;
    cin>>m>>n>>k;
    vector<vector<ll>> grid;
    for(int i=0; i<m; i++) {
        vll temp;
        for(int j=0; j<n; j++){
            ll x ; cin >> x;

            temp.push_back(x);
        }

        grid.push_back(temp);
    }

    ll xOr = 0;

    queue<pair<int, int>> q;
    vector<vector<bool>> vis(m, vector<bool>(n, false));
    vis[0][0] = true;
    ll path = 0;
    q.push({0, 0});

    while(!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        xOr ^= grid[i][j];
        
        if(xOr == k  && i == m-1 && j == n-1){
            path++;
        }

        for(auto& v : dir) {
            int new_i = i + v[0];
            int new_j = j + v[1];

            if((new_i >= 0 && new_i < m && new_j >= 0 && new_j < n) && (!vis[new_i][new_j])){
                vis[new_i][new_j] = true;
                q.push({new_i, new_j});
            }
        }

        
    }
    cout << path << "\n";

    return 0;
}