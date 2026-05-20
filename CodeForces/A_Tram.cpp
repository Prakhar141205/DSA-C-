#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    int currC = 0;
    int max_C = INT_MIN;
    while(n--){
        int ai, bi;

        cin >> ai >> bi;
        currC = currC - ai + bi ;

        max_C = max(currC, max_C);
        


    }

    cout << max_C <<"\n";
    return 0;
}