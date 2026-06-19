class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        // maximum score achieved
        int result = 0;
        // current score during gameplay
        int score = 0;
        // sort tokens so we can use the smallest first and the largest last
        sort(tokens.begin(), tokens.end());
        // two-pointer method
        // left  : smallest token
        // right : largest token
        int left = 0;
        int right = tokens.size() - 1;
        // process tokens while there are still some left
        while (left <= right) {
            // play face up if we have enough power for the smallest token
            if (power >= tokens[left]) {
                // spend power equal to token value
                power -= tokens[left];
                // move left pointer to next token
                left++;
                // gain one score
                score++;
                // update maximum score
                result = max(result, score);
            }
            // if we cannot play face up but have some score, play face down
            else if (score > 0) {
                // regain power from the largest token
                power += tokens[right];
                // remove that token from consideration
                right--;
                // lose one score
                score--;
            }
            // cannot play face up and cannot play face down no more moves are possible
            else {
                break;
            }
        }
        // return the maximum score obtained
        return result;
    }
};

// Time Complexity : O(Nlog)
// Space Complexity : O(1)


class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        int n = tokens.size();
        int l=0, r=n-1;
        sort(tokens.begin(), tokens.end());
        int score = 0, max_score = 0;
        while(l <= r){

            if(power >= tokens[l]){
                power -= tokens[l];
                score++;
                max_score = max(score, max_score);
                l++;
            }

            else if(score > 0){
                power += tokens[r];
                r--;
                score--;
                // max_score = max(score, max_score);
            }else{
                return max_score;
            }

            
        }
        return max_score;
    }
};