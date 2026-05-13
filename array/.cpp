class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<int> diff (2*limit+2, 0);

        for(int i=0; i<n/2; i++){
            int a = nums[i];
            int b = nums[n-1-i];
            int low = min(a, b)+1;
            int high = max(a, b)+limit;

             int sum = a + b;

            // assume 2 moves
            diff[2] += 2;

            // range starts
            diff[low] -= 1;

            // 0 move => exact sum
            diff[sum] -= 1;

            // back to 1 move
            diff[sum + 1] += 1;

            // back to 2 moves
            diff[high + 1] += 1;

        }


        int ans = INT_MAX;
        int curr = 0;

        for(int s = 2; s <= 2 * limit; s++) {
            curr += diff[s];
            ans = min(ans, curr);


        }

        return ans;

    }
};

class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<int> diff(2 * limit + 2, 0);

        for (int i = 0; i < n / 2; ++i) {
            int a = min(nums[i], nums[n - 1 - i]);
            int b = max(nums[i], nums[n - 1 - i]);

            diff[2] += 2;
            diff[a + 1] -= 1;
            diff[a + b] -= 1;
            diff[a + b + 1] += 1;
            diff[b + limit + 1] += 1;
        }

        int min_ops = n;
        int current_ops = 0;

        for (int c = 2; c <= 2 * limit; ++c) {
            current_ops += diff[c];
            min_ops = min(min_ops, current_ops);
        }

        return min_ops;
    }
};

class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int complementaryMaxSum= 2*limit+2;// just added +2 in case of array bounds
        vector<int> sweepLine(complementaryMaxSum,0);// complementary sum range : [2,2*limit];
        vector<int> pairMapSum(complementaryMaxSum,0);
        int n=nums.size();
        for(int i=0,j=n-1;i<j;)
        {
            pairMapSum[nums[i]+nums[j]]++;
            int mnPossible=1+min(nums[i],nums[j]);
            int mxPossible= max(nums[i],nums[j])+limit;
            sweepLine[mnPossible]++;
            sweepLine[mxPossible+1]--;
            i++;
            j--;
        }
        for(int i=1;i<complementaryMaxSum;i++) sweepLine[i]+=sweepLine[i-1];

        // Linear search on all possible complementary sums : [2,2*limit+2];
        int ans=INT_MAX;
        for(int i=2;i<complementaryMaxSum;i++)
        {
            // No of sweepLine segments that intersect at i. (conceptually it is no of pairs that can have i as their sum with atMax 1 move)
            int part1=sweepLine[i];

            // No of sweepLine segments that dont intersect at i.(2Moves)
            int part2=(n/2-part1)*2;// n-2*part1
           
            // no need of moves pairs (o moves)
            int part3=pairMapSum[i];

            ans=min(ans,part1+part2-part3);
        }
        return ans;

    }
};

class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<int> boundaries(2 * limit + 2, 0);  
        int left = 0, right = n - 1;
        
        while (left < right) {
            int lower = min(nums[left], nums[right]);
            int higher = max(nums[left], nums[right]);

            int mn = lower + 1;
            int mx = higher + limit;

            boundaries[2] += 2;
            boundaries[mn] -= 1;

            boundaries[nums[left] + nums[right]] -= 1;
            boundaries[nums[left] + nums[right] + 1] += 1;

            boundaries[mx + 1] += 1;

            left++;
            right--;
        }

        int res = INT_MAX;
        int num_to_change = 0;
        for (int i = 2; i < boundaries.size(); i += 1) {
            num_to_change += boundaries[i];
            res = min(res, num_to_change);
        }

        return res;
    }
};