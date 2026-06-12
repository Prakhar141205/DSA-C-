#include <bits/stdc++.h>

using namespace std;

int largestSubarrayWithSumK(vector<int> vec, int k){
    int n = vec.size();
    int ans=INT_MIN;
    for(int i=0; i<n; i++){
        for(int j=i; j<n; j++){
            int sum=0;
            for(int k=i; k<=j; k++){
                sum += vec[k];
            }
            if(sum == k){
                ans = max(ans, j-i+1)
            }
        }
    }
    return ans;
}
int main(){
    vector<int> vec = {1, 2, 3, 4};
    int  k = 9;
    cout << "Max length with sum K = "<<largestSubarrayWithSumK(vec, k)<<"\n";
    return ;
}