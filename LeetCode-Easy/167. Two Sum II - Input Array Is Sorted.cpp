class Solution {
public:
    vector<int> twoSum(vector<int>& arr, int t) {
            int n = arr.size();

            int l=0, r= n-1;
            
            while(l < r){
                if(arr[l] + arr[r] > t){
                    r--;
                }else if(arr[l] + arr[r] < t){
                    l++;
                }else {

                    break;
                }
            }
        return  {l+1, r+1};
    }
};

// TC O(n)