// using sorting 
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<int>result;
        int n=nums.size();
        int ct=1;
        for(int i=1;i<=n;i++){
            if(i<n && nums[i]==nums[i-1]){
                ct++;
            }
            else{
                if(ct>n/3){
                    result.push_back(nums[i-1]);
                }
                ct=1;
            }
        }
        return result;
    }
};


// using maps
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> ans;
        unordered_map<int, int> mpp;
        for (int i = 0; i < nums.size(); i++) {
            mpp[nums[i]]++;
        }
        for (auto it : mpp) {
            if (it.second > nums.size() / 3 &&
                find(ans.begin(), ans.end(), it.first) == ans.end())
                ans.push_back(it.first);
        }
        return ans;
    }
};

// Booyer Moore Voying ALgorithm

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int cd1=0;
        int cd2=1;
        int cnt1=0;
        int cnt2=0;
        int s=nums.size();
        for(int n:nums){
            if(cd1==n)cnt1++;
            else if(cd2==n)cnt2++;
            else if(cnt1==0){
                cd1=n;
                cnt1=1;
            }else if(cnt2==0){
                cd2=n;
                cnt2=1;
            }else{
                cnt1--;
                cnt2--;
            }
        }
        vector<int>ans;
        cnt1=cnt2=0;
        for(int n:nums){
           if(n==cd1)cnt1++;
           else if(n==cd2)cnt2++;
        }

        if(cnt1>s/3)ans.push_back(cd1);
        if(cnt2>s/3)ans.push_back(cd2);
        return ans;
    }
}