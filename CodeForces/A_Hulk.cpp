#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
     
    int n;
    cin >> n;
    string ans = "";
    for(int i=1; i<=n; ++i){
        
    
            if(i % 2 == 0) ans += "I love that ";
            else ans += "I hate that ";
        }
    ans.replace(ans.size()-6, 5, " it");

    cout << ans <<"\n";
    return 0;
}