#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
     
    int n;
    cin >> n;

    while(n--){
        int a, b;
        cin >> a >> b;
        if (a % b == 0) cout << 0 << "\n";
        else cout << (b*((a/b)+1) - a) <<"\n";

     
    }
    return 0;
}
