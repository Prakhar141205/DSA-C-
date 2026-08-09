class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();

        vector<int> rightHandMatchedLength(n, 0) ;
        int  i = n-1;
        int j = m-1;
        int rightHandMatched = 0;
        while(i >= 0) {

            if(j >= 0 && word1[i] == word2[j]) {
                rightHandMatched++;
                j--;
            }
            rightHandMatchedLength[i] = rightHandMatched;
            i--;
        }


        vector<int> ans ;
        i =0, j=0;
        bool hasPower = true;
        while(i < n && j < m) {
            if(word1[i] == word2[j]) {
                ans.push_back(i);
                j++;
            }else if(hasPower == true && i + 1 < n && rightHandMatchedLength[i+1] >= m - j - 1 ) {
                hasPower = false;
                ans.push_back(i);
                j++;
            }

            i++;
        }

        return j == m ? ans : vector<int> () ;
        
    }
};