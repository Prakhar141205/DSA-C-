#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<int> freq(1001, 0);

        ll sum = 0;
        int maxFreq = 0;
        int maxValue = 0;

        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;

            sum += x;
            freq[x]++;

            if (freq[x] > maxFreq) {
                maxFreq = freq[x];
                maxValue = x;
            }
        }

        int other = n - maxFreq;

        if (maxFreq <= other + 1) {
            cout << sum << '\n';
        }
        else {
            int usable = other + 2;
            ll otherSum = sum - 1LL * maxFreq * maxValue;

            cout << otherSum + 1LL * usable * maxValue << '\n';
        }
    }

    return 0;
}