#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
 
void sum(int n, int i) {
    if(n == 0) {
         cout << i << " ";
         return;
    }

    sum(n-1, i+n);
   
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sum(10, 0);

    return 0;
}