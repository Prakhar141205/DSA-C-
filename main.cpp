#include <bits/stdc++.h>

using namespace std;

class Solution{
public:
    int noLeaders(vector<int>& vec){
        int leaders=1;
        
        int n = vec.size();

        int maximum = vec[n-1];

        
        
        for(int i=n-2; i>=0; i--){
            if( vec[i] > maximum) leaders++; // set stores the element in non decreasing order
            
            if(maximum < vec[i]) maximum = vec[i];
;        }

        return leaders;
    }
};
int main(){
    vector<int> vec = {10, 22, 12, 3, 0, 6};

    Solution s;

    cout << "No of leaders are " << s.noLeaders(vec) << "\n";
    return 0;
}