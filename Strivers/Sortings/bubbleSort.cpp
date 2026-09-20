#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
 
void bubbleSort(vector<int>& arr) {
    int n = arr.size();

    for(int i=0; i<n-2; i++) {
        bool isSwap = false;
        for(int j=0; j<n-i-1; j++) {

            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                isSwap = true;
            }
        }

        if(isSwap == false) break ; // array gets sorted
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {1, 2, 5, 4, 3, 6};

    bubbleSort(arr);

    for(int x : arr) {
        cout << x << " ";
    }

    cout << endl;
    return 0;
}