#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    set<char> name;
    for(char c : s){
        name.insert(c);
    }
    int sz=name.size();
    if( ((sz >> 1) << 1) == sz-1) cout << "IGNORE HIM!\n";
    else cout << "CHAT WITH HER!\n";
    return 0;
}