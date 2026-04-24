#include <iostream>
#include <vector>
#include <string>
using namespace std;


void merge(vector<int>& nums, int st, int mid, int end){
    vector<int> temp;
    int i = st;
    int j = mid+1;

    while(i <= mid && j <= end){
        if(nums[i] <= nums[j]){
            temp.push_back(nums[i++]);
        }else{
            temp.push_back(nums[j++]);
        }
    }

    while(i <= mid){
            temp.push_back(nums[i++]);
        }

        while(j <= end){
            temp.push_back(nums[j++]);
        }
    for(int x=st, y=0; x<=end; x++){
        nums[x]=temp[y++];
    }
}

void mergeSort(vector<int> &nums, int st, int end){
    if(st >= end) return ;
    int mid = st + (end-st)/2;
    mergeSort(nums, st, mid);
    mergeSort(nums, mid+1, end);

    merge(nums, st, mid, end );

}
int main(){

    vector<int> nums = {3,2,4,5,6,2,7,2,2};
    int n = nums.size();
    mergeSort(nums, 0, n-1);

    for(int x : nums){
        cout << x << " ";
    }
    cout << endl;
    return 0;
}