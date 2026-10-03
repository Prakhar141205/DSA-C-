class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n = strs.size();

        string ans = strs[0];
        for(int i=1; i<n; i++)  {

            string temp = "";
            int k = 0;

            for(int j=0; j<strs[i].length(); j++) {
                if(k < ans.length() && ans[k] == strs[i][j]) {
                    temp += strs[i][j];
                    k++;
                }else {
                    break;
                }


            }
            ans = temp ;
        }

        return ans;
        
    }
};