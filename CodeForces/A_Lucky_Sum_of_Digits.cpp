#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

using vi = vector<int>;
using vll = vector<ll>;
using vpii = vector<pii>;
using vpll = vector<pll>;

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;

#define pb push_back
#define forn(i, n) for (int i = 0; i < (n); i++)

void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

int main() {
    fastIO();

    int n ; cin >> n ;
    int bestA = -1;
    int bestB = -1;

    int minDigits = INT_MAX;

    for(int b=0; b<= n/7; b++) {
        int a = (n - 7 * b) ;
        if(a % 4 == 0) {
            int digits = a/4 + b ;

            if(digits < minDigits ) {
                minDigits = digits;
                bestA = a/4;
                bestB = b ;
            }

            if(digits == minDigits && a/4 > bestA){
                    bestA = a/4;
                    bestB = b;
            }
        }

    }

    if(bestA == -1) cout << -1 << "\n";
    else {
        string res = "";
        while(bestA--){
            res += "4";
        }
        while(bestB--){
            res += "7";

        }

        cout << res << "\n";
    }
    return 0;
}