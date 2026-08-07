class Solution {
public:
    int n ;

    bool isPred(string prev, string curr) {
        int l1 = prev.length();
        int l2 = curr.length() ;

        if(l1 >= l2 || l2 - l1 != 1) {
            return false;
        }
        int i=0, j=0;

        while(i < l1 && j < l2 ) {
            if(prev[i] == curr[j]) {
                i++;
            }

            j++;
        }

        return i == l1 ;
    }
    int lis(vector<string>& words, int curr_idx, int prev_idx) {
        if(curr_idx == n ) return 0;

        int taken = 0 ;

        if(prev_idx == -1 || isPred(words[prev_idx], words[curr_idx])) {
            taken = 1 + lis(words, curr_idx+1, curr_idx) ;
        }

        int not_taken = lis(words, curr_idx+1, prev_idx) ;

        return max(taken, not_taken) ;
    }
    int longestStrChain(vector<string>& words) {
        n = words.size() ;

        auto lambda = [&] (string& s, string& t) {
            return s.length() < t.length() ;
        };

        sort(words.begin(), words.end(), lambda) ;

        return lis(words, 0, -1);
    }
};