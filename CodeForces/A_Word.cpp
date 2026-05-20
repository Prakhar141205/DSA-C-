#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int upperCase = 0, lowerCase = 0;
    for(char c : s){
        if(c >= 'A' && c <= 'Z') upperCase += 1;
        else lowerCase += 1;
    }

   
    string ans = "";
    if(upperCase > lowerCase){
        for(int i=0; i<s.size(); ++i){
           char ch = s[i];
            if(ch >= 'a' && ch <= 'z'){
                ans += (char)(ch - 'a' + 'A');
            }else {
                ans += ch;
            }
        }
    }else{
        for(int i=0; i<s.size(); ++i){
            char ch = s[i];
            if(ch >= 'A' && ch <= 'Z'){
                ans  += (char)(ch - 'A' + 'a');
            }else{
                ans += ch;
            }
        }

    }

    cout << ans << "\n";
    return 0;
}