class Solution {
public:
    int canEatInGivenSpeed(vector<int>& piles, int currSpeed, int totalTime) {
        int timeTaken = 0;

        for(int i=0; i<piles.size(); i++) {
            timeTaken += (piles[i] / currSpeed) ;
            if(piles[i] % currSpeed != 0) {
                timeTaken += 1;
            }
        }
        return timeTaken <= totalTime;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        int n = piles.size();
        int l=1, r = *max_element(begin(piles), end(piles));

        while(l < r) {
            int mid = l + (r-l) / 2;

            if(canEatInGivenSpeed(piles, mid, h)) {
                r = mid;
            }else {
                l = mid + 1;
            }
        } 

        return l ;  
    }
};