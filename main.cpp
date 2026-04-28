/*vector<int> vec {nums.begin(), nums.end()}*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int mod = 1e9 + 7;

// using prefix array 
int numOfSub(vector<int> nums){
    int n = nums.size();
    vector<int> prefix;
    prefix[0] = nums[0];
    for(int i=1; i<n; i++){
        prefix[i] = prefix[i-1] + nums[i];
    }

    int count=0; 
    int even = 1; // to overcome the corner cases 
    int odd = 0;

    for(int i=0; i<n; i++){
        if(nums[i] % 2 == 0){
            count = (count + odd) % mod;
            even++;
        }else{
            count = (count+even)%mod;
            odd++;
        }
    }
    return count;
}

// without prefix array
int numOfSub(vector<int> nums){
    int n = nums.size();
    vector<int> prefix;
    prefix[0] = nums[0];
    for(int i=1; i<n; i++){
        prefix[i] = prefix[i-1] + nums[i];
    }

    int count=0; 
    int even = 1; /*to overcome the corner cases  because 0 is also an even sum 
    => it is including the subarray with single element */
    int odd = 0;
    int sum=0;
    for(int i=0; i<n; i++){
        sum += nums[i];
        if(sum % 2 == 0){
            count = (count + odd) % mod;
            even++;
        }else{
            count = (count+even)%mod;
            odd++;
        }
    }
    return count;
}
int main(){

    return 0;

}