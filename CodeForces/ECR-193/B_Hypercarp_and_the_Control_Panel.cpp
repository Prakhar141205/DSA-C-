#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    if (n == 1) {
        cout << 1 << "\n";
        return;
    }

    // Step 1: Calculate baseline count without any swaps
    int base_count = 1;
    for (int i = 1; i < n; ++i) {
        if (a[i] != a[i - 1]) {
            base_count++;
        }
    }

    int max_extra = 0;

    // Step 2: Check all adjacent pairs to see how swapping them changes the sequence
    for (int i = 0; i < n - 1; ++i) {
        if (a[i] == a[i + 1]) continue; // Swapping identical values yields no change

        // Calculate original local contributions around indices i and i+1
        int original_local = 1; // for the edge between a[i] and a[i+1]
        if (i > 0 && a[i] != a[i - 1]) original_local++;
        if (i + 2 < n && a[i + 1] != a[i + 2]) original_local++;

        // Calculate new local contributions after simulating a swap (a[i] and a[i+1])
        int swapped_local = 1; // for the new edge between a[i+1] and a[i]
        if (i > 0 && a[i + 1] != a[i - 1]) swapped_local++;
        if (i + 2 < n && a[i] != a[i + 2]) swapped_local++;

        max_extra = max(max_extra, swapped_local - original_local);
    }

    cout << base_count + max_extra << "\n";
}

int main() {
    // Optimize input/output operations for speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int TestsNumT;
    cin >> TestsNumT;
    while (TestsNumT--) {
        solve();
    }
    return 0;
}
