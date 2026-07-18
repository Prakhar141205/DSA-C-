class Solution {
public:
    int minIncrementForUnique(vector<int>& arr) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int moves = 0;
        for(int i=1; i<n; i++) {
            int diff = (arr[i] - arr[i-1]) ;
            if(diff <= 0) {
            arr[i] = arr[i-1] + 1;
            moves += abs(diff) + 1;
            }
        }
        return moves;
    }
};

// Approach 2 using cnting cort
class Solution {
public:
    int minIncrementForUnique(vector<int>& arr) {
        int n = arr.size();

       auto M = *max_element(arr.begin(), arr.end());

        vector<int> cnt(1e5+1e5, 0);

        for(int& x : arr) cnt[x]++;

        int moves = 0;
        for(int i=1; i <= cnt.size(); i++) {
            int extra = cnt[i-1] - 1 ;
            if(extra >= 0){
            cnt[i] += extra;
            moves += extra;
            }
        
    }

    return moves;
    }
};

