#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int year ;
    cin >> year;

    int ans = year + 1;

    while(ans++){
        string s = to_string(ans);

        for(char c : s){
            s.insert(c);
        }

        if(s.size() == 4){
            cout << ans << "\n";
            break;
        }else{
            s.clear();

        }
    }
    return 0;
}