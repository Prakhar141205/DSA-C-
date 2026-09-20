
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

int partition(vector<int>& arr, int l, int r) {
    int pivot = arr[r];
    int pi = l;

    for(int i=l; i < r; i++) {

        if(arr[i] <= pivot) {
            swap(arr[i], arr[pi++]);
        }
    }

    swap(arr[pi], arr[r]) ;

    return pi ;
}
void quickSort(vector<int>& arr, int l, int h) {
    if(l >= h) return;
    int pi = partition(arr, l, h);

    quickSort(arr, l, pi-1);
    quickSort(arr, pi+1, h);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {2, 1, 5, 4 , 8, 3};

    quickSort(arr, 0, arr.size()-1);

    for(int x : arr) cout << x << " ";

    return 0;
}