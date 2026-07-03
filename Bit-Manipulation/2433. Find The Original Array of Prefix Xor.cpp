class Solution {
public:
    vector<int> findArray(vector<int>& pref) {
        int n = pref.size();

        vector<int> arr(n, 0);

        arr[0] = pref[0];

        for(int i=1; i<n; i++) { 

            arr[i] = (pref[i] ^ pref[i-1]) ; 
        }
        
        return arr;
    }
};

// for modifying the same array we need to loop from the end to start and use the same logic as above