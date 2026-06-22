class Solution {
public:
    int maxNumberOfBalloons(string text) {
        if(text.length() < 7) return 0;
        vector<int> cnt(26, 0);

        for(char& c : text) cnt[c-'a']++;
        for(int x : cnt) cout << x << " ";

        string t = "balloon";

        int ans=cnt['b' - 'a'];

        for(char& e : t)
            if(e == 'l' || e == 'o')
                ans = min(cnt[e-'a']/2, ans);

            else ans = min(cnt[e-'a'], ans);
        

        return ans;
    }
};