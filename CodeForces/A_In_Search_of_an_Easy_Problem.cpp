#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int count = 0;
    while(n--){
        int x;
        cin >> x;
        count = max(count, x);
       
    }

    cout << (count > 0 ? "HARD" : "EASY");
    
    return 0;
}