#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
   cin.tie(NULL);

   string x, y;
   cin >> x >> y;
   
   
    string ans = "";
   for(int i=0; i<x.size(); ++i){
    char a = x[i];
    char b = y[i];
    if(a == b ) ans += '0';
    else ans += '1';
   }

cout << ans <<"\n";

    return 0;
}