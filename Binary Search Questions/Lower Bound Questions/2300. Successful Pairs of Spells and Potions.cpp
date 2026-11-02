class Solution {
public:

    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        int n = spells.size();
        int m = potions.size();
        vector<int> ans(n);
        sort(begin(potions), end(potions));

        int maxPotion = potions[m-1];

        for(int i=0; i<n; i++) {
            int spell = spells[i];

            long long minPotion = ceil(1.0*success / spell) ;

            if(minPotion > maxPotion) {
                ans[i] = 0;
                continue;
            }

            auto idx = lower_bound(begin(potions), end(potions), minPotion) ;
            ans[i] = end(potions) - idx;
        }

        return ans;
    }
};


class Solution {
public:
    int apna_lower_bound(int l, int r, vector<int>& potions, long long minPotion) {
        int ans = -1;

        while(l <= r) {
            int m = l + (r-l)/2;

            if(potions[m] < minPotion) {
                l = m + 1;
            }else {
                ans = m;
                r = m -1 ;
            }
        }

        return ans;
    }
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        int n = spells.size();
        int m = potions.size();
        vector<int> ans(n);
        sort(begin(potions), end(potions));

        int maxPotion = potions[m-1];

        for(int i=0; i<n; i++) {
            int spell = spells[i];

            long long minPotion = ceil(1.0*success / spell) ;

            if(minPotion > maxPotion) {
                ans[i] = 0;
                continue;
            }

            auto idx = lower_bound(begin(potions), end(potions), minPotion) ;
            ans[i] = end(potions) - idx;
        }

        return ans;
    }
};