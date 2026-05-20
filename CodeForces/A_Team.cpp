#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;   // number of test cases
    int sP = 0;
    while(t--){
        int a, b, c;

        cin >> a >> b >> c;

        if((a + b + c) >= 2 ) sP += 1;



    }
    cout << sP << endl;
    

    return 0;
}