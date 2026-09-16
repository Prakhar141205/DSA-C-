#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define all(x) std::begin(x), std::end(x)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int arr[5] = {1, 2, 3, 4, 5};
    cout << "Sum: " << *max_element(all(arr));


    return 0;
}