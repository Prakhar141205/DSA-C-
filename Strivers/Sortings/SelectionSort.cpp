#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
 

void selectionSort(vector<int>& arr) {

    int n = arr.size();

    for(int i=0; i<n-1; i++) {
        int j=i+1, minIdx = i ;

        while(j < n) {
            if(arr[j] < arr[minIdx]) {
                minIdx = j;
            }

            j++;
        }
        swap(arr[minIdx], arr[i]);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {1, 2, 5, 4, 3, 6};

    selectionSort(arr);

    for(int x : arr) {
        cout << x << " ";
    }

    cout << endl;
    return 0;
}