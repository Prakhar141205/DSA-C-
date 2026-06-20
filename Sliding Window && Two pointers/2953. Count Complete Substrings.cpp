class Solution {
public:
    int solve(int st, int end, string word, int k){
        int result=0;

        // checking for the unique chars in the given string
        for(int unique_chars = 1; unique_chars <= 26 && unique_chars*k <= end - st + 1; unique_chars++){

            vector<int> count(26, 0); // map to store the count of the chars in the string 
            int good_chars = 0; // chars with freq = k

            // start sliding window
            int i = st;
            // current window length => unique chars* k
            int window_length = unique_chars*k;

            for(int j=st; j<= end; j++){
                    char ch = word[j];
                    count[ch-'a']++;

                    if(count[ch - 'a'] == k){
                        good_chars += 1;
                    }else if(count[ch-'a'] == k+1){
                        good_chars -= 1;
                    }

                    // decrease the size of window
                    if(j - i + 1 > window_length){
                        if(count[word[i]-'a'] == k){
                            good_chars -= 1;
                        }else if(count[word[i] - 'a'] == k+1){
                            good_chars += 1;
                        }

                        count[word[i] - 'a']--;
                        i++;
                    }

                    if(good_chars == unique_chars){
                        result++;
                    }
            }

            
        }       
            return result;


    }
    int countCompleteSubstrings(string word, int k) {
        int n = word.size();
        int last = 0, result = 0;

        // step 1: marks the boudary to satisfy the second conditon 
        // after making boundaries no need to think of second condition
        // because these parts of string contains that part of string which is satisfying the condition 2

        for(int i=1; i<=n; i++){
            if(i == n || abs(word[i] - word[i-1]) > 2){

            
            result += solve(last, i-1, word, k);
            last = i;
        }
    }
        return result;
    }
};