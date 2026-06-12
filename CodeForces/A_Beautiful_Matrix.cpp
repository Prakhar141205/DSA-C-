#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int r=5;
    int r1, c1;
    while(r--){
        int c = 5;
        while(c--){
            int n;
            cin >> n;

            if(n == 1){
                c1 = c;
                r1 = r;
            }
        }
    }

    cout << abs(3-r1) + abs(3-c1) << "\n";
    return 0;
}