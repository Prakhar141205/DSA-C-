class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& customers) {
        double n = customers.size();
        double chefTime = customers[0][0] + customers[0][1];
        double avgTime = customers[0][1];
        
        for(int i=1; i<n; i++ ) {
            if(chefTime >= customers[i][0]) {
                chefTime += customers[i][1];
                cout << chefTime << "\n";
            }else {
                chefTime = customers[i][0] + customers[i][1];
                cout << chefTime << "\n";
            }

            avgTime += (chefTime - customers[i][0]);
            // cout << avgTime << "\n";
        }
        

        double ans = avgTime / n ;
        cout << ans << " ";
        return ans;
    }
};