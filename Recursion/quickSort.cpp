#include <iostream>
#include <vector>
#include <string>
using namespace std;

int partition(vector<int> &nums, int st, int end){
    int it = st-1;
    int pivot = nums[end];

    for(int i=st; i<end; i++){
        if(nums[i] <= pivot){
            it++;
            swap(nums[i], nums[it]);
        }
    }
    it++; //  giving correct place to the pivot
    swap(nums[it], nums[end]);

    return it;
}

void quickSort(vector<int> &nums, int st, int end){
    if(st >= end ) return ;

    int pivot = partition(nums, st, end);

    quickSort(nums, st, pivot-1);
    quickSort(nums, pivot + 1, end);
}


int main(){

    vector<int> nums = {3,2,4,5,6,2,7,2,2};
    int n = nums.size();
    quickSort(nums, 0, n-1);

    for(int x : nums){
        cout << x << " ";
    }
    cout << endl;
    return 0;
}


/*
Even though pivot and nums[end] 
have the same value, pivot is just a separate variable,
 not part of the array. Swapping with pivot only changes that variable 
 and not the array’s structure. To correctly place the pivot in the array, 
 you must swap using nums[end], which represents the actual element inside the array.
 */