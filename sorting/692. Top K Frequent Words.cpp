class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        int n = words.size();

        sort(begin(words), end(words));

        int i = 0;
        vector<pair<string, int>> res;
        while(i < n) {
            string c = words[i];
            int cnt = 0;

            while(i < n && c == words[i]) {
                cnt++;
                i++;
            }

            res.push_back({c, cnt});
        }
        
        sort(begin(res), end(res), [](auto a, auto b) {
            if(a.second != b.second ) {
                return a.second > b.second ;
            }
            return a.first < b.first;

        } ) ;
        for(auto [x , y] : res) {
            cout << x << " " << y << endl;
        }
        vector<string> ans;

        for(int i=0; i<k; i++) {
            cout << res[i].first << " \n";
            ans.push_back(res[i].first);
        }
        return ans;
    }
};