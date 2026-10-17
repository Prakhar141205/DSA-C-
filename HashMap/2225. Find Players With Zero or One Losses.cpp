class Solution {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        unordered_map<int, int> winner; // winner, no of times winner wins
        unordered_map<int, int> looser; // looser no of times looser losses

        for(auto match : matches) {

            winner[match[0]] += 1;

            looser[match[1]] += 1;

        }
        
        for(auto [p, cnt] : looser) {
                cout << p << " " << cnt << endl;
 
        }

        vector<vector<int>> ans;

        vector<int> winnerResult;
        vector<int> looserResult;

        for(auto [wins, cnt] : winner ){

            if(looser.find(wins) == looser.end()) {
                winnerResult.push_back(wins);
            }
        }

        for(auto [losr, cnt] : looser) {
            if(cnt == 1 ) {
                looserResult.push_back(losr);
            }
        }

        sort(begin(winnerResult), end(winnerResult));
        sort(begin(looserResult), end(looserResult));

        ans.push_back(winnerResult);
        ans.push_back(looserResult);

        // for(auto a : ans) {
        //         int p = a[0];
        //         int cnt = a[1];

        //         cout << p << " " << cnt << endl;
 
        // }
        return ans;
    }
};