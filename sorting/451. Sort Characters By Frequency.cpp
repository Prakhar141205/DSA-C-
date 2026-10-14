class Solution {
public:
    string frequencySort(string s) {
        sort(begin(s), end(s));
        int n = s.length();
        int i = 0;
        vector<pair<char, int>> ans;
        while(i < n) {
            char cc = s[i];
            int cnt = 0;

            while(i < n && s[i] == cc) {
                cnt++;
                i++;
            }

            ans.push_back({cc, cnt});
        }

        sort(begin(ans), end(ans), [](auto a, auto b) {
            return a.second > b.second;
        });

        string temp = "";
        for(auto [c , t] : ans) {
            cout << c << " " << t << endl;
            while(t--) {
                temp += c;
            }

        }

        
        return temp;
    }
};