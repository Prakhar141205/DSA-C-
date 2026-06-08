class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        int l = landStartTime.size();
        int w = waterStartTime.size();
        int finalResult = INT_MAX;
        // first start from land

        for(int i=0; i<l; i++){

            for(int j=0; j<w; j++){
            int Land = landStartTime[i] + landDuration[i];
            int water = waterStartTime[j] + waterDuration[j];
                int land_water = max(Land, waterStartTime[j]) + waterDuration[j];
                finalResult = min(land_water, finalResult);

                int water_land = max(water, landStartTime[i]) + landDuration[i];

                finalResult = min(water_land, finalResult);
            }
        }

        
        return finalResult;
    }
};