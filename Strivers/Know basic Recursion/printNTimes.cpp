#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

void print(int n) {

    if(n == 0) return;

    print(n-1);
    cout << "Prakhar: " << n << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    print(5);
    

    return 0;
}