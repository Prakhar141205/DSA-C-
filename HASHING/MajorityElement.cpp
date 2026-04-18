#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

void majorityElement(vector<int> nums){
    iny n = nums.size();
    unordered_map<int, int> mp;

    for(int i=0; i<n; i++){
        if(mp.count(nums[i])){
            mp[nums[i]]++;
        }else{
            mp[nums[i]]=1;
        }
    }

    for(pair<int, int> x:mp){
        if(x.second > n / 3){
            cout << x.first << " ";
        }
    }
    cout << endl;
}
int main(){
    vector<int> arr = {1, 3, 4, 5, 5, 5, 6, 6, 4, 5, 5, 5};

    majorityElement(arr);
    return 0;
}