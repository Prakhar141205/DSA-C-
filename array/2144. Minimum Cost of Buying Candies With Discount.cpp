class Solution {
public:
    int minimumCost(vector<int>& cost)
    {
        sort (cost.begin(),cost.end());
        int ans=0;
        for (int i=cost.size()-1 ; i>=0 ; i--)
        {
            if (i>=1) ans+=cost[i]+cost[i-1];
            else if (i==0) ans+=cost[i];
            i-=2;
        }
        return ans;
    }
};

class Solution {
public:
    int minimumCost(vector<int>& cost) {
        int n= cost.size();

        sort(cost.begin(), cost.end());
        int ans=0;
        int totSum=0, remCost=0;
        for(int i=n-1; i>=0; i--){
            totSum += cost[i];
        }
        

        for(int i=n-3; i>=0; i-=3){
            remCost += cost[i];
        }

         ans = totSum - remCost;

        return ans;
    }
};