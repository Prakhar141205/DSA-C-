#include <iostream>
#include <vector>
#include <string>
using namespace std;

// print all subsets if all the elements of the array are unique
void printAllSub(vector<int> arr, vector<int> &ans, int i){
    if(i == arr.size()){
        for(int val : ans){
            cout << val << " ";

        }
        cout << endl;
        return;
    }

    // include
    ans.push_back(arr[i]);
    printAllSub(arr, ans, i+1);
    // exclude
    ans.pop_back();
    printAllSub(arr, ans, i+1);
}


// print all the unique subsets if all the elements are not unique => repetition is allowed
int main(){
    vector<int> arr = {1, 3, 4};
    vector<int> ans;

    printAllSub(arr, ans, 0);
    return 0;
}