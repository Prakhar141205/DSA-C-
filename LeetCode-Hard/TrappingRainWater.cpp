/* three approaches 
1. using array leftmax and right_max
2. using stack 
3. using leftmax and right max variable constant space 
4. using DP
*/

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();

        vector<int> left_max(n, 0);
        vector<int> right_max(n, 0);
        left_max[0] = height[0];
        
        // get left max
        for(int i=1; i<n; i++){
            left_max[i] = max(left_max[i-1], height[i]);
        }

        right_max[n-1] = height[n-1];
        // get right max
        for(int i=n-2; i>=0; i--){
           
            right_max[i] = max(right_max[i+1], height[i]);
        }
        int ans=0;
        // ans = min(leftmax, rightmax) - currheight
        for(int i=0; i<n; i++){
            ans += min(left_max[i], right_max[i]) - height[i];
        }

        return ans;
        
    }
};

// 2. using leftmax and right max variable
class Solution {
public:
    int trap(vector<int>& arr) {
        int l = 0,r = arr.size()-1;
        int lmax = 0,rmax = 0,total = 0;
        while(l < r){
            if(arr[l] <= arr[r]){
                if(lmax > arr[l]){
                    total += (lmax - arr[l]);
                }
                else{
                    lmax = arr[l];
                }
                l++;
            }
            else{
                if(rmax > arr[r]){
                    total += (rmax - arr[r]);
                }
                else{
                    rmax =  arr[r];
                }
                r--;
            }
        }
        return total;
    }
};

// using stack

class Solution {
public:
    int trap(vector<int>& height) {
       stack <pair<int,int>> st;
       int total = 0;
       for(int i = 0; i < height.size(); i++){
        while(!st.empty() &&  st.top().first < height[i]){
            int cur = st.top().first;
            st.pop();
            int rwall = height[i];
            int lwall = st.empty()? -1 : st.top().first;
            int lidx = st.empty()? -1 : st.top().second;
            if(lwall != -1){
                total += max(0, (min(lwall, rwall) - cur)*(i-lidx - 1));
            }
        }
        st.push({height[i], i});
       }
       return total;
    }
};