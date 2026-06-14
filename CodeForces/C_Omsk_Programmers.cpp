#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Solves a single testcase
void solve() {
    long long a, b, x;
    cin >> a >> b >> x;

    // Vectors to store the pairs of {value, number of division steps taken}
    vector<pair<long long, long long>> pathA, pathB;

    // Generate division sequence for 'a'
    long long stepsA = 0;
    pathA.push_back({a, stepsA});
    while (a > 0) {
        a /= x;
        stepsA++;
        pathA.push_back({a, stepsA});
    }

    // Generate division sequence for 'b'
    long long stepsB = 0;
    pathB.push_back({b, stepsB});
    while (b > 0) {
        b /= x;
        stepsB++;
        pathB.push_back({b, stepsB});
    }

    // Evaluate all combinations to find the minimum operations
    long long min_ops = 2e18; // Use an appropriately large value for initialization
    for (auto const& pA : pathA) {
        for (auto const& pB : pathB) {
            long long current_valA = pA.first;
            long long current_valB = pB.first;
            long long operations = pA.second + pB.second + abs(current_valA - current_valB);
            
            min_ops = min(min_ops, operations);
        }
    }

    cout << min_ops << "\n";
}

int main() {
    // Fast I/O for competitive programming environments
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
