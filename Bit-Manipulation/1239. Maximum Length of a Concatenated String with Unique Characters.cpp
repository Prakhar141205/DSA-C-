class Solution {
public:
    void solve(int idx, int temp, int& result, vector<int>& uniqueCharsStrings ) {
        int n = uniqueCharsStrings.size();

        result = max(result, __builtin_popcount(temp));

        for(int i=idx; i<n; i++) {
            if ((temp & uniqueCharsStrings[i]) == 0)
                solve(i+1, temp | uniqueCharsStrings[i], result, uniqueCharsStrings);
        }
    }
    int maxLength(vector<string>& arr) {
        // to store all the unique character strings in bitmask form
        // ith set bit in the bitmask will represent the presence of ith  character in the string starting from a = 0, b = 1, c = 2 and so on in binary representation
        vector<int> uniqueCharsStrings;

        for(auto& s: arr) {
            // store all the unique characters in a set and check if the size of the set is equal to the length of the string, if not then it means that there are duplicate characters in the string and we can skip that string
            unordered_set<char> st(s.begin(), s.end());

            if(st.size() != s.length()) {
                continue;
            }

            int val = 0;
            
            // preparing a bitmask for each of the unique strings and storing it in the uniqueCharsStrings vector
            for(char& ch : s) {
                val = (val | (1 << (ch - 'a')));
            }  

            uniqueCharsStrings.push_back(val); 
        }

        int result=0;
        int temp = 0;

        solve(0, temp, result, uniqueCharsStrings);

        return result;
        
    }
};