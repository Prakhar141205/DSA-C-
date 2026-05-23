class Solution {
public:
    bool check(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return true;
        int inversionCount = 0;
        for (int i = 1; i < n; ++i) {
            if (nums[i] < nums[i - 1]) {
                inversionCount++;
                if (inversionCount > 1) return false;
            }
        }
        if (nums[0] < nums[n - 1]) inversionCount++;
        return inversionCount <= 1;
    }
};

class Solution {
public:
    bool check(vector<int>& nums) {
        int n=nums.size();
        int peak=0;
        
       for(int i=0;i<n;i++){
        if(nums[i]>nums[(i+1)%n]) peak++;
       }

       if(peak>1) return false;
       return true;
    }
};

class Solution {
public:
    bool check(vector<int>& nums) {

        vector<int> temp = nums;

        sort(temp.begin(), temp.end());

        int n = nums.size();

        for(int x = 0; x < n; x++) {

            vector<int> rotated(n);

            for(int i = 0; i < n; i++) {

                int pos = (i + x) % n;

                rotated[i] = temp[pos];
            }

            if(rotated == nums) {
                return true;
            }
        }

        return false;
    }
};

class Solution {
public:
    bool check(vector<int>& nums) {
        int n= nums.size();
        int i = n-1;
        while(i >0 && nums[i-1] <= nums[i]){
            i--;
        }
        if(i == 0 )return true;
        for(int j = i ; j <(i+n)-1;j++){
            if(nums[j%n] > nums[(j+1)%n]){
                return false;
            }
        }
        return true;
    }
};

class Solution {
public:

    vector<int> rotateArray(vector<int> nums, int k) {

        int n = nums.size();

        rotate(nums.begin(), nums.begin() + k, nums.end());

        return nums;
    }

    bool check(vector<int>& nums) {

        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());

        int n = nums.size();

        for(int i = 0; i < n; i++) {

            if(nums == rotateArray(sorted, i)) {
                return true;
            }

        }

        return false;
    }
};

class Solution {
public:
    bool check(vector<int>& nums) {
        int n=nums.size(),count=0;
        for(int i=0;i<2*n-1;i++)
        {
            if(nums[i%n]>nums[(i+1)%n])
            count++;
        }
        if(count<3)
        return true;
        return false;
    }
};