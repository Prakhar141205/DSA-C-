#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--) {
        int n ;
        cin >> n;
        int cnt1 = 0, cnt0 = 0;

        bool first = false;
        bool last = false;

        for(int i=0; i<n; i++) {
            int x; cin >> x;

            if(x == 0) {
                cnt0++;
            }else {
                cnt1++;
            }

            if(x == 0 && i == 0) first = true;
            if(x == 0 && i == n-1) last = true;
        }

        if(cnt0 < 2) cout << -1 << "\n";
        else {

            cout << !first + !last << "\n";
        } 
    }

    return 0;
}