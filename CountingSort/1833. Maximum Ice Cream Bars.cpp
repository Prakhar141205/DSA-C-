class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        vector<int> cnt(1e5+1, 0);

        for(int& x:costs) cnt[x]++;
        int ans=0;
        for(int i=1; i<cnt.size(); i++){
            if(cnt[i] == 0) continue;

            int can_buy = min(cnt[i], coins/i); // find minimum no of ice creams can buy 

            ans += can_buy;
            coins -= can_buy * i;

            if(coins < i) break;
        }
        return (int)ans;
    }
};