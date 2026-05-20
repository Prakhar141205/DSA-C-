#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int X=0;
    while(n--){
        string s;
        cin >> s;
        if(s == "++X" || s == "X++") X++;
        else X--;
    }


    cout << X << "\n";
    return 0;
}