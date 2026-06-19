class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        int n = people.size();

        int  l=0, r=n-1;
        sort(people.begin(), people.end());

        int boat=0;

        while(l <= r){
            int sum = people[l] + people[r];

            if(sum <= limit){
                boat++;
                l++; r--;
            }
            if (sum > limit){
                boat++;
                r--;
            }
        }
        return boat;
    }
};

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        int n = people.size();
        vector<int> count(limit+1, 0);

        for(int i = 0; i<n; i++){
            count[people[i]]++;
        }
        int minboats = 0;
        int l = 1;
        int r = limit;
        
        while(l <= r){
            if(count[r] <= 0){
                r--;
                continue;
            }
            if(count[l] <= 0){
                l++;
                continue;
            }
            if(l + r <= limit){
                count[l]--;
                
            }
        
            count[r]--;
            minboats++;
            
        }

        return minboats;
    }
};