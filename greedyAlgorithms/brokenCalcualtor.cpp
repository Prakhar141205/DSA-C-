class Solution {
public:
    int brokenCalc(int startValue, int target) {
        if(startValue >= target) return startValue - target;

        // even
        if(target%2 == 0) return 1 + brokenCalc(startValue, target/2);

        return 1 + brokenCalc(startValue, target+1);
    }
};

while((stval < target)){
    if(target%2 == 0){
        cnt++;
        target /= 2;
    }else{
        cnt++;
        target += 1;
    }
}

cnt += (stval - target)