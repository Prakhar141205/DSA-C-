// Optimally, go from left to right in that order. After this, the height of tower i
//  will be min(a1,a2,…,ai)
// , so the minimum sum is a1+min(a1,a2)+min(a1,a2,a3)+⋯
// .

// Time complexity: O(n)

#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int x = 10000, y = 0;
        for (int i = 0; i < n; ++i) {
            int z;
            cin >> z;
            x = min(x, z), y += x;
        }
        cout << y << '\n';
    }
    return 0;
}