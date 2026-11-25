class Solution {
public:
    int minimumPushes(string word) {
        int n = word.length();

        vector<int> cnt(26, 0);
        for(char c : word) {
            cnt[c-'a']++;
        }

        sort(begin(cnt), end(cnt), greater<int> ());
        int res = 0;

        for(int i=0; i<26; i++) {
            res += (cnt[i] * (i/8 + 1)) ;
        }

        return res;
    }
};