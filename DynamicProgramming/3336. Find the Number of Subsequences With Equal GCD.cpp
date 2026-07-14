class Solution {
public:
    const int mod =  1e9+7;
    int n ;

    int solve(vector<int>& nums, int idx, int gcdS1, int gcdS2) {
        if(idx == n) {
            bool isNonEmpty = gcdS1 != 0 && gcdS2 != 0 ;
            bool gcdsMatch = (gcdS1 == gcdS2) ? 1 : 0;

            return (isNonEmpty && gcdsMatch);
        }

        int skip = solve(nums, idx+1, gcdS1, gcdS2)  ;
        int addToSeq1 = solve(nums, idx+1, __gcd(gcdS1, nums[idx]), gcdS2) ;
        int addToSeq2 = solve(nums, idx+1, gcdS1, __gcd(gcdS2, nums[idx])) ;

        return (skip+addToSeq1+addToSeq2) ;
    }

    int subsequencePairCount(vector<int>& nums) {
         n = nums.size();
        
        return solve(nums, 0, 0, 0) ;
        
    }
};

// bottom up Approach
class Solution {
public:
    const int mod =  1e9+7;
    int n ;

    int subsequencePairCount(vector<int>& nums) {
        n = nums.size();
        auto maxVal = max_element(nums.begin(), nums.end());

        int dp[n+1][*maxVal+1][*maxVal+1] ;

        // fill the base case

        for(int i=0; i<= *maxVal; i++) {
            for(int j=0; j <= *maxVal; j++) {
                bool isNonEmpty = (i != 0 && j != 0) ;
                bool gcdsMatch = (i == j);
                dp[n][i][j] = (isNonEmpty && gcdsMatch) ? 1 : 0;
            }
        }

        // bottom up from last idx to first 
        for(int i=n-1; i>=0; i--) {

            for(int first = *maxVal; first >= 0; first--) {
                for(int second = *maxVal; second >= 0; second--) {
                        int skip = dp[i+1][first][second]  ;

                        int addToSeq1 = dp[i+1][__gcd(first, nums[i])][second] ;

                        int addToSeq2 = dp[i+1][first][__gcd(second, nums[i])] ;

                        dp[i][first][second] =  (0LL + skip + addToSeq1 + addToSeq2) % mod;
                }
            }
        }
        return dp[0][0][0] ;
        
    }
};