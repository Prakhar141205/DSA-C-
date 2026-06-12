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
    
}

// -------------------- Main --------------------
int main() {
    fastIO();

    int n, m;
    cin >> n >> m;
    int cnt=1;
    for(int i=0; i<n; i++){

        if(i % 2==0){
            for(int k=0; k<m; k++){
                cout << '#';
            }

        }else{
            if(cnt%2 != 0)
                for(int j=0; j<m; j++){
                if(j == m-1) cout << '#';
                else cout << '.';
            }

            else{
                for(int j=0; j<m; j++){
                if(j == 0) cout << '#';
                else cout << '.';
            }
            
        }
        cnt++;
    }
    cout << "\n";
    }
    return 0;
}