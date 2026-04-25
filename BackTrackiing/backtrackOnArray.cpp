#include <iostream>
#include <vector>
#include <string>

void printArr(int* arr, int n){
    for(int x : arr){
        cout << x << " ";
    }
    cout << endl;
}

void backTrackOnArray(int* arr, int n, int idx){
    if(idx == n){
        printArr(arr, n);
        return ;
    }

    arr[i] = i+1;
    backTrackOnArray(arr, n, 0);

}

int main(){

    int arr[6] = {0};
    int n = 6;

    backTrackOnArray(arr, n, 0);
    return 0;
}