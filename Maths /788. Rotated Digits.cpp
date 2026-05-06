// Brute force Method

class Solution {
public:
    bool isSameDiff(int x ){
        bool isOnly018 = true;

        while(x > 0){
            int dig = x % 10;

            if(dig == 3 || dig == 4, dig == 7) return false;
            else if(dig == 2 || dig == 5 || dig == 6 || dig == 9) isOnly018 = false;

            x = x/10;
        }
        if(isOnly018) return false;
        else return true;
    }
    int rotatedDigits(int n) {
        int cnt = 0;
        
        for(int i=1; i<=n; i++){
            cnt += isSameDiff(i);
        }

        return cnt ;
        
    }
};



// optimal using digit DP

// precalculate the answer for 0 to 9
class Solution {
public:
    
    int rotatedDigits(int n) {
        vector<int> dp(n+1, 0); 
        int cnt = 0;
        // 0 => invalid 
        // 1 => same but valid
        // 2 => diff and valid 

        for(int i=0; i<=n; i++){
            // initialising dp vector
            if(i < 10 ){
                if(i == 0 || i == 1 || i == 8) dp[i]=1; // valid but same
                else if(i == 2 || i == 5 || i == 6 || i == 9) { // valid but diff
                    dp[i]=2;
                    cnt++;
                }
            }else{ // 
                int remNum = dp[i/10];
                int lastDig = dp[i%10];

                if(remNum == 1 && lastDig == 1){ // case when all dig are 0 1 8
                    // in this case no increaes in cnt only fill the dp vector
                    dp[i]=1;
 
                }else if(remNum >= 1 && lastDig >= 1){// atleast one of the digit is 2, 5, 6, 9
                    dp[i]=2;
                    cnt++;
                }

            }
        }
        return cnt;
    }
};


// using recursion

class Solution {
public:
    int rotatedDigits(int n) {
        vector<int> digits = {0, 1, 2, 5, 6, 8, 9};
        string s = to_string(n);
        // idx, tight, valid, started
        vector<vector<vector<vector<int>>>> dp(s.size(), vector<vector<vector<int>>>(2, vector<vector<int>> (2, vector<int>(2,-1))));

        return solve(s, 0, true, false, false, digits, dp);
    }

    int solve(string& s, int idx, bool tight, bool valid, bool started, vector<int>& digits, vector<vector<vector<vector<int>>>>& dp) {
        if(idx == s.size()) return valid;

        if(dp[idx][tight][valid][started] != -1) return dp[idx][tight][valid][started];

        int ans = 0;
        int limit = tight ? s[idx] - '0' : 9;
        for(int i: digits) {
            if(i > limit) break;
            int ntight = tight && (i == limit);
            if(!started && i == 0) {
                ans += solve(s, idx + 1, ntight, false, false, digits, dp);
            }
            else if(!valid && (i == 0 || i == 1 || i == 8)) {
                ans += solve(s, idx + 1, ntight, false, true, digits, dp);
            }
            else {
                ans += solve(s, idx + 1, ntight, true, true, digits, dp);
            }
        }
        return dp[idx][tight][valid][started] = ans;
    }
};

// using strings
class Solution {
public:
    bool isValid(int num){
        string sn = to_string(num);
        int index = 0,
            len = sn.size();
        if(sn.contains('3') ||
           sn.contains('4') ||
           sn.contains('7')) return false;
        else if(sn.contains('2') ||
                sn.contains('5') ||
                sn.contains('6') ||
                sn.contains('9')) return true;
        /*else if(sn.contains('4')) return false;
        else if(sn.contains('7')) return false;*/
        
        return false;
    }
    int rotatedDigits(int n) {
        int cnt = 0;
        for(int i=1;i<=n;i++){
            if(isValid(i)) cnt++;
        }
        //cout<<isValid(13);
        return cnt;
    }
};