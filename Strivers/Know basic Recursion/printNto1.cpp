#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

void print(int n ) {
    if(n == 0 ) return;

    cout << n << " ";
    print(n-1);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    print(10);

    return 0;
}