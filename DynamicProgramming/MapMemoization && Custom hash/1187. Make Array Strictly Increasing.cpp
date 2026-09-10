// Good question to understand the concept of memoization instead of using simple 2d array for the memoization 

class Solution {
public:
    // unordered map can't be used because of that it is not able to hash the pair as the key

    map<pair<int, int>, int> mp;
    // unordered_map<pair<int, int>, int> mp;

    int solve(vector<int>& arr1, vector<int>& arr2, int i, int prev) {

        if(i >= arr1.size()) return 0;

        if(mp.find({i, prev}) != mp.end()) return mp[{i, prev}];

        int result1 = 1e9 + 2, result2 = 1e9+2;

        if(arr1[i] > prev) { // here array1 is strictly increasing so we can skip
            result1 = solve(arr1, arr2, i+1, arr1[i]);

        }
    
        auto it = upper_bound(arr2.begin(), arr2.end(), prev);

        if(it != arr2.end()) {
            int j = it - arr2.begin();
            int newPrev = arr2[j];

            result2 = 1 + solve(arr1, arr2, i+1, newPrev);
        }

        return mp[{i, prev}] = min(result1, result2);
    }
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        sort(begin(arr2), end(arr2));
        mp.clear();
        int result = solve(arr1, arr2, 0, INT_MIN);

        return result == 1e9+2 ? -1 : result ;
        
    }
};