class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n  = nums.size();

        if (n == 1) return 0;
        int st = find(begin(nums), end(nums), 0) - begin(nums);

        bool asc = true, dsc = true;

        for(int i=1; i<n; i++) {
            int val = nums[ (st + i ) % n] ;
            if (val != i)  asc = false;
            if(val != n - i ) dsc = false;
            if(!asc && !dsc) return -1; 
        }

        if(asc) return min(st, n-st+ 2);

        return min(n-st, st+2);



    }
};