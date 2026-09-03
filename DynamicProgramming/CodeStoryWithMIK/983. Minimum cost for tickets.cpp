class Solution {
public:
    int n;
    int t[366];
    int solve(vector<int>& days, vector<int>& costs, int i) {
        if(i >= n) return 0;
        if(t[i] != -1) return t[i];
        int j = i;

        int cost1 = costs[0] + solve(days, costs, i+1);

        j = i ;
        int max_days = days[i] + 7 ;

        while(j < n && days[j] < max_days) j++;

        int cost2 = costs[1] + solve(days, costs, j);

        j = i ;
        max_days = days[i] + 30 ;

        while(j < n && days[j] < max_days) j++;

        int cost3 = costs[2] + solve(days, costs, j);

        return t[i] = min({cost1, cost2, cost3});


    }
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        n = days.size();
        memset(t, -1, sizeof(t));
        return solve(days, costs, 0);
        
    }
};

// bottom up
class Solution {
public:
    int n;
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        n = days.size();
        int last_day = days[n-1];

        unordered_set<int> st(days.begin(), days.end()) ;

        vector<int> t(last_day+1, 0) ;
        t[0] = 0 ;
        // t[i] cost required to reach till ith day
        
        for(int i=1; i<=last_day; i++) {

            if(st.find(i) == st.end()) {
                t[i] = t[i-1];
                continue;
            }

            int cost_1 = costs[0] + t[max(i-1, 0)] ;
            int cost_2 = costs[1] + t[(max(i-7, 0))] ;
            int cost_3 = costs[2] + t[(max(i-30, 0))] ;

            t[i] = min({cost_1, cost_2, cost_3}) ;
        }

        return t[last_day];
        
    }
};