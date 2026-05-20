#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n ;
    cin>>n;
    int z = n;
    double x = 0.0;

    while(n--){
        int y;
        cin >> y;

        x += y;

    }
    cout << fixed << setprecision(12);
    cout << (x)/ (double)z <<"\n";
    return 0;
}