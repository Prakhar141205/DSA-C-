#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    double k, n, w;

    cin >> k >> n >> w;

    double x = ((k/2.0)*w*(w+1));
    
    if (x < n) cout << 0 <<"\n"; // he has enough money
    else cout << (int)(x - n) << "\n";
    return 0;
}