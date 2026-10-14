class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size();
        int k = 0;
        int i=0;
        while(i < n) {
            char curr_char = chars[i];
            int cnt = 0;

            while(i < n && chars[i] == curr_char) {
                cnt++;
                i++;
            }

            chars[k] = curr_char;
            k++;
            if(cnt > 1) {
                string curr = to_string(cnt);
                for(char c : curr) {
                    chars[k] = c;
                    k++;
                   
                }
            }
        }

        return k;
    }
};