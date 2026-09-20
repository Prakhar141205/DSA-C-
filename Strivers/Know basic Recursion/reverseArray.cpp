#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
void rev(int* arr, int i, int j) {
    if(i >= j) {
        return;
    }

    swap(arr[i], arr[j]);
    rev(arr, i+1, j-1);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int arr[5] = {1, 3, 4, 5, 6};

    rev(arr, 0, 4) ;

    for(int x : arr) cout << x << " ";
    return 0;
}