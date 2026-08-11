#include <bits/stdc++.h>
using namespace std;
int main() {
ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n; cin >> n ;
        vector<int> a(n);
        for(int i=0; i<n; i++) {
            cin >> a[i]; 
        }

        int base_score = 1 ;

        for(int i=0; i<n-1; i++) {
            base_score += (a[i] != a[i+1]) ;
        }

        int max_delta = 0;

        for(int i=0; i<n-1; i++) {
            if(i+1 < n && a[i] == a[i+1]) continue;

            int delta = 0;

            if(i > 0) delta += (a[i-1] != a[i+1] ) - (a[i-1] != a[i]) ;

            if(i + 2 < n ) delta += (a[i] != a[i+2]) - (a[i+1] != a[i+2]) ;

            max_delta = max(max_delta, delta) ;
        }

        cout << base_score + max_delta << "\n" ;
    }

    return 0;
}