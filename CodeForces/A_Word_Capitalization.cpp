#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    if(s[0] >= 'a' && s[0] <= 'z'){
            s[0] = s[0] - 'a' + 'A';
    }
    

    cout << s <<"\n";
 
    return 0;
}