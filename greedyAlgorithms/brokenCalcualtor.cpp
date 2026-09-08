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

// Using BFS
class Solution {
public:
    int brokenCalc(int startValue, int target) {
        queue<int> q;
        q.push(target);

        int ops = 0;

        while(!q.empty()) {
            int cur = q.front();
            q.pop();

            if(cur <= startValue) {
                return ops + startValue - cur;
            }

            if(cur % 2 == 0) {
                q.push(cur / 2);
            }else {
                q.push(cur + 1);
            }

            ++ops;
        }
        return -1 ;
    }
};