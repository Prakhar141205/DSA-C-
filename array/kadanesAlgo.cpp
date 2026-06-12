#include <bits/stdc++.h>

using namespace std;
void print(vector<int> vec){
    int n = vec.size();
    int maxSum = -98, ansStart=-1, ansEnd=-1;
    int start=0;
    int sum=0;
    for(int i=0; i<n; i++){
        if(sum == 0) start=i;
        sum += vec[i];
        if(sum < 0) sum = 0;

        if(sum > maxSum){
            maxSum = sum;
            ansStart = start;
            ansEnd = i;
        }
    }

    for(int i=ansStart; i<=ansEnd; i++){
        cout << vec[i] << " ";
    }
}
int main(){
    vector<int> vec = {1, -2,  3, 4};
    int  k = 9;
   print(vec);
    return 0;
}