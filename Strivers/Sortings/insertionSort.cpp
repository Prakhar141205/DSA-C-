#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
 
void insertionSort(vector<int>& arr) {
    int n = arr.size();

    for(int i=1; i<n; i++) {

        int curr = arr[i];
        int j = i-1;

        while(j >= 0 && arr[j] > curr) {
            arr[j+1] = arr[j];
            j--;
        }

        arr[j+1] = curr;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {1, 2, 5, 4, 3, 6};

    insertionSort(arr);

    for(int x : arr) {
        cout << x << " ";
    }

    cout << endl;
    return 0;
}