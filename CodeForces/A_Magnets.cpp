#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int count = 0;
    string prev = "";
    while(n--){
        string s;
        cin>> s;

        if(prev != s) count++;

        prev = s;


       
    }

    cout << count <<"\n";
    
    return 0;
}