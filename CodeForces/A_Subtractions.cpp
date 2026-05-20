#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int ans=0;
    while(n--){
        int a, b;
        cin >> a >> b;
        while(a > 0 && b > 0){
            if(a > b) {
               ans += a/b;
               a = a%b;
                }
            else  {
                ans += b/a;
                b = b%a;

            }
            
        }

        cout << ans <<"\n";
        ans = 0;
    }
    return 0;
}