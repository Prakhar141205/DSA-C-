#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n>> k;

    int c = 0;
    while(c < k){
        if(n % 10 != 0){
            n--;
            c++;
        }else{
            n /= 10;
            c++;
        }
    }

    cout << n << "\n";
    return 0;
}