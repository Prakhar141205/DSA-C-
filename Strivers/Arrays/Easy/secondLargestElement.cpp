#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {1, 2, 3, 4, 65 , 0};
    
    int largest = INT_MIN;
    int second_large = INT_MIN;

    for(int i=0; i<arr.size(); i++) {

        if(arr[i] > largest) {
            second_large = largest;
            largest = arr[i];
            
        }else if(arr[i] > second_large && arr[i] != largest) {
            second_large = arr[i];
        }
    }

    cout << "Largest " << largest << endl;
    cout << "Second Largest " << second_large << endl;
    return 0;
}