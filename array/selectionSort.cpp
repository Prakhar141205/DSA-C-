#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void selectionSort(vector<int> &nums){
    int n = nums.size();

    for(int i=0; i<n-1; i++){
        int minIdx = i;
        

        for(int j=i+1; j<n; j++){
            if(nums[j] < nums[i]){
                minIdx=j;
            }
        }

        swap(nums[minIdx], nums[i]);
    }
}

void bubbleSort(vector<int> &nums){
    int n = nums.size();

    for(int i=0; i<n-1; i++){// swaps

        for(int j=0; j<n-i-1; j++){
            
            if(nums[j] > nums[j+1]){
                swap(nums[j], nums[j+1]);
            }
        }
    }
}

int partition(vector<int> &arr, int &lb, int &ub){
    int st = lb;
    int end = ub;
    int pivot = arr[lb];

    while(st < end){
        while(arr[st] <= pivot) st++;
        while(arr[end] > pivot) end--;

        if(st < end) swap(arr[st], arr[end]);
    }
    swap(arr[end], arr[lb]);

    return end;
}

void quickSort(vector<int> &arr, int lb, int ub){
    
    if (ub > lb){
    int loc = partition(arr, lb, ub);

    quickSort(arr, lb, loc-1);
    quickSort(arr, loc+1, ub);
}
}

int main(){

    vector<int> nums = {2, 4, 6, 8, 5,4 ,3 , 23, 234, 2};

    quickSort(nums, 0, nums.size()-1);

    for(int &x : nums){
        cout << x << " ";
    }
    cout << endl;
    return 0;
}