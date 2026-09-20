#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> temp;
    int i = l, j=m+1;
    while(i <= m && j <= r) {

        if(arr[i] < arr[j]) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }

    while(i <= m) {
        temp.push_back(arr[i++]);
    }

    while(j <= r) temp.push_back(arr[j++]);

    int k=0;
    for(int i=l; i<=r; i++) {
        arr[i] = temp[k++];
    }
}
void mergeSort(vector<int>& arr, int l, int r) {

    if(l >= r) return;

    int mid = l + (r-l)/2;

    mergeSort(arr, l, mid);
    mergeSort(arr, mid+1, r);

    merge(arr, l, mid, r);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr  = {1, 2, 4, 5, 3, 2 , 1};
    int l =0 , r =arr.size()-1 ;

    mergeSort(arr, 0, 6);


    for(int x : arr) cout << x << " ";
    return 0;
}

