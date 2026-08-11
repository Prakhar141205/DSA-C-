#include <bits/stdc++.h>
using namespace std;
int main() {
ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int a, b, c; cin >> a >> b >> c;
        int M = max({a, b, c}) ;
        int sum = a + b + c ;
        int ri = M - min({a, b, c}) ;

        int rf = (sum - M) - min({a, b, c}) ;

        cout << min(ri, rf)<<"\n";


        
    }

    return 0;
}