#include <iostream>

#include <vector>

using namespace std;



int main(){
    int arr[5] = {1, 2, 3, 4, 5};
    int W = 9;

    vector<vector<int>> ans;
    vector<int> subset;

    allSubset(arr, 5, subset, ans);

    for(auto v : ans){
        for(int x : v) cout << x << " ";
        cout << endl;
    }
    return 0;
}