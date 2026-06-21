class Solution {
public:
    int minLights(vector<int>& lights) {
        int n = lights.size();
        for(int i=0; i<n; i++){
            if(lights[i]){
            int pos = max(0, i - lights[i]);

            lights[pos] = max(lights[pos], lights[i]);
            }
        }

        int ans=0;
        int coverage = 0;

        for(int i=0; i<n; i++){
            if(lights[i] == 0 && coverage == 0){
                ans++;
                if(i + 1 < n && lights[i+1] == 0){
                    coverage=3;
                }
            }
            coverage--;
            coverage = max(coverage, lights[i]);
        }
        return ans;
        
    }
};