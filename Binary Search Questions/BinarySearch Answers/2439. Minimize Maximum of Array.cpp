class Solution {
public:
    bool isValid(vector<int>& nums, int mid_max, int n) {
        vector<long long> arr(begin(nums), end(nums));

        for(int i=0; i<n-1; i++ ) {
            if(arr[i] > mid_max) return false;

            long long buffer = mid_max - arr[i];
            arr[i+1] = arr[i+1] - buffer;
        }

        return arr[n-1] <= mid_max;
    }
    int minimizeArrayValue(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        int maxL = 0;
        int maxR = *max_element(begin(nums), end(nums));

        while(maxL <= maxR) {
            int mid_max = maxL + (maxR-maxL) / 2;

            if(isValid(nums, mid_max, n)) {
                ans = mid_max;
                maxR = mid_max - 1;
            }else {
                maxL = mid_max+1;
            }
        }

        return  ans;
    }
};

// 
#include <bits/stdc++.h>
using namespace std;

/*
    LeetCode 2439 - Minimize Maximum of Array

    Key invariant:
    Values can move only to the LEFT. Therefore, for every prefix [0..i],
    its total sum must fit into (i+1) positions, each <= X:

        prefixSum(i) <= (i+1) * X

    Thus X must be at least ceil(prefixSum(i)/(i+1)) for every prefix.
    These bounds are achievable, so the answer is the maximum prefix
    ceiling-average.

    Each class below is an independent implementation. For LeetCode,
    rename the chosen class to Solution.
*/


// 1. Brute force over possible answers + prefix feasibility.
// Time: O(n * max(nums)); Space: O(1). Educational only; too slow for 1e9.
class SolutionBruteForceAnswer {
private:
    bool feasible(const vector<int>& nums, long long limit) {
        long long prefixSum = 0;
        for (int i = 0; i < (int)nums.size(); ++i) {
            prefixSum += nums[i];
            if (prefixSum > limit * (i + 1LL)) return false;
        }
        return true;
    }

public:
    int minimizeArrayValue(vector<int>& nums) {
        int high = *max_element(nums.begin(), nums.end());
        for (int x = 0; x <= high; ++x) {
            if (feasible(nums, x)) return x;
        }
        return high;
    }
};


// 2. Binary search on answer + prefix-sum feasibility.
// Time: O(n log(max(nums)+1)); Space: O(1).
class SolutionBinarySearchPrefix {
private:
    bool feasible(const vector<int>& nums, long long limit) {
        long long prefixSum = 0;
        for (int i = 0; i < (int)nums.size(); ++i) {
            prefixSum += nums[i];
            if (prefixSum > limit * (i + 1LL)) return false;
        }
        return true;
    }

public:
    int minimizeArrayValue(vector<int>& nums) {
        int low = 0;
        int high = *max_element(nums.begin(), nums.end());

        while (low < high) {
            int mid = low + (high - low) / 2;
            if (feasible(nums, mid)) high = mid;
            else low = mid + 1;
        }
        return low;
    }
};


// 3. Binary search + right-to-left surplus simulation.
// Time: O(n log(max(nums)+1)); Space: O(1).
// Excess at i must move to i-1; any remaining excess keeps moving left.
class SolutionBinarySearchSurplus {
private:
    bool feasible(const vector<int>& nums, long long limit) {
        long long surplus = 0;

        for (int i = (int)nums.size() - 1; i >= 1; --i) {
            long long current = nums[i] + surplus;
            surplus = max(0LL, current - limit);
        }
        return nums[0] + surplus <= limit;
    }

public:
    int minimizeArrayValue(vector<int>& nums) {
        int low = 0;
        int high = *max_element(nums.begin(), nums.end());

        while (low < high) {
            int mid = low + (high - low) / 2;
            if (feasible(nums, mid)) high = mid;
            else low = mid + 1;
        }
        return low;
    }
};


// 4. Optimal one-pass prefix-average greedy.
// Time: O(n); Space: O(1).
class SolutionOptimalPrefixAverage {
public:
    int minimizeArrayValue(vector<int>& nums) {
        long long prefixSum = 0;
        long long answer = 0;

        for (int i = 0; i < (int)nums.size(); ++i) {
            prefixSum += nums[i];

            // ceil(prefixSum / (i+1)), using integer arithmetic.
            long long required = (prefixSum + i) / (i + 1LL);
            answer = max(answer, required);
        }
        return (int)answer;
    }
};


// 5. Optimal one-pass running ceiling-average (equivalent formulation).
// Time: O(n); Space: O(1).
class SolutionOptimalRunningAverage {
public:
    int minimizeArrayValue(vector<int>& nums) {
        long long sum = 0;
        long long answer = 0;

        for (long long length = 1; length <= (long long)nums.size(); ++length) {
            sum += nums[length - 1];

            long long average = sum / length;
            if (sum % length != 0) ++average;

            answer = max(answer, average);
        }
        return (int)answer;
    }
};


/*
    Dry run: nums = [3, 7, 1, 6]

    Prefix [3]:       ceil(3/1)  = 3
    Prefix [3,7]:     ceil(10/2) = 5
    Prefix [3,7,1]:   ceil(11/3) = 4
    Prefix [3,7,1,6]: ceil(17/4) = 5

    Answer = max(3,5,4,5) = 5.

    About the submitted isValid():
    It scans left-to-right and subtracts the capacity (limit-arr[i])
    from arr[i+1]. This can make arr[i+1] negative, which is not a valid
    operation state: a position cannot transfer units it does not own.
    Use the prefix feasibility check (Approach 2) or surplus check
    (Approach 3) instead.

    Recommended submission: SolutionOptimalPrefixAverage (Approach 4).
*/
