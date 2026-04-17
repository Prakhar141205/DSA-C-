// Implementation of Max heap
#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

void heapify(vector<int> &
    vec, int i, int n){
    int l = 2*i+1;
    int r = 2*i + 2;

    int maxI = i;

    if(l < n && vec[l] > vec[maxI]){
        maxI = l;
    }

    if(r < n && vec[r] > vec[maxI]){
        maxI = r;

    }

    swap(vec[i], vec[maxI]);

    if(maxI != i){
        heapify(vec, maxI, n);
    }
}
void heapSort(vector<int> &vec){
    int n = vec.size();

    // build a Max Heap
    for(int i=n/2 - 1; i>=0; i--){ // call heapify for all non leaf nodes
        heapify(vec, i, n);
    }

    // taking element to correct position
    for(int i=n-1; i>=0; --i){
        swap(vec[0], vec[i]);

        heapify(vec, 0, i);
    }
}

int main(){
    vector<int> vec = {12, 24, 245, 32, 42};

    heapSort(vec);

    for(int x : vec){
        cout << x <<" ";
    }
    cout << endl;
    return 0;
}