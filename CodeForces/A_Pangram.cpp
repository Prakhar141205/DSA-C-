#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
     
    int n;
    cin >> n;

    string s;
    cin >> s;
    vector<bool> alpha(26, false);
    int x = s.size();
    for(int i=0; i<x; i++){
        if(s[i] >= 'A' && s[i] <= 'Z'){
            s[i] = s[i] - 'A' + 'a';
        }
    }

    for(int i=0; i<x; i++){
        alpha[s[i] - 'a'] = true;
    }

    bool isTrue = false;
    for(int i=0; i<26; ++i){
        if(!alpha[i]) isTrue=true;
    }

    if(isTrue) cout << "NO\n";
    else cout << "YES\n";

    

    
    return 0;
}
