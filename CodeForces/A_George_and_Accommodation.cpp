#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, ans=0;
    cin >> n;

    while(n--){
        int a, b;
        cin >> a >> b;

        if((b - a) >= 2){
            ans++;
        }
    }
    cout << ans << "\n";
    return 0;
}