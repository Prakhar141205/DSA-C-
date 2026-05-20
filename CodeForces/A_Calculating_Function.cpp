#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    long long int n;
    cin >> n;
    
    if(n % 2 == 0){
        cout << (n/2) << "\n";
    }else{
        cout << -1*((n+1)/2) << "\n";
    }
    return 0;
}