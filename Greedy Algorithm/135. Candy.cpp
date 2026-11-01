class Solution {
public:
//brute force approach will be pehle left ngb se compare kro agr rating badhi to plus krte jao 
//phir ek aur iteration mein right ngb se compare kro ki i+1 se rating badh rhi ho to plus krte jao 
//phir ek aur iteration krke dono ko max bcz vo ith candy i-1 and i+1 dono ki rating se jo satisy kregi vo max hogi in dono ka 
//optimal approach would be slope based intuition ki agr ratings ko draw toh ek graph bnta hua dikh rha hoga 
//to kya kro increasing slope mein agr ith rating pichle se badhi heh toh peak badhate jao 
//and running sum mein add krdo phir flat bhi aaksta hai to sirf 1 hi add kro sum 
//phir decreasing slop aaye phir 1 se count krke shuru kro and sum mein add krdo 
//(but in reality hme decreasing slope ke neeche se countin shuru krni chahaiye but vo kaise kre na upar se decreasing de skte ki minus 1 krte jay bcz start nhi pta to upar se neeche hi aate heh +1 krte huye and down variable mein plus one add krte gya and sum mein down add krdiya toh jo sbse top element jaha se shuru kra woh peakd increasing slope ka akhri and decreasing ka pehla toh intersect hua toh jo increasing slop mein peak calculate ki and decreasing mein down agr down - peak ka kuch difference hua toh woh add krdege mtlb peak toh already added but agr down zyada hua toh topmost down hona chhaiye toh isliye add krdege)
    int candy(vector<int>& ratings) {
        // int n = ratings.size();
        // vector<int>l(n,1);
        // vector<int>r(n,1);
        // for(int i = 1; i<n; i++){
        //     if(ratings[i]>ratings[i-1]){
        //         l[i] = l[i-1] + 1;
        //     }
        // }
        // for(int i = n-2; i>=0; i--){
        //     if(ratings[i]>ratings[i+1]){
        //         r[i] = r[i+1] + 1;
        //     }
        // }
        // int sum = 0;
        // for(int i = 0; i<n; i++){
        //     sum += max(l[i],r[i]);
        // }
        // return sum;

        int n = ratings.size();
        int i = 1;
        int sum = 1;
        while(i<n){
            if(ratings[i]==ratings[i-1]){
                sum++;i++;continue;
            }
            int peak = 1;
            while(i<n && ratings[i]>ratings[i-1]){
                peak++;
                sum += peak;
                i++;
            }
            int down = 1;
            while(i<n && ratings[i]<ratings[i-1]){
                sum+=down;
                i++;
                down++;
            }
            if(down >= peak)sum+=down-peak;
        }
        return sum;
    }
};