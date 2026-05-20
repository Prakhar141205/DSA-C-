#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t;
    cin >> s>> t;
    int n = s.size();
    if(n != t.size()) cout <<"NO\n";
    else{

        for(int i=0; i < n/2; ++i){
            swap(s[i], s[n-i-1]);
        }

        // cout << s;
        if(s == t) cout <<"YES\n";
        else cout <<"NO\n";
    }

    return 0;
}