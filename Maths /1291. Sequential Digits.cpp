class Solution {
public:     
    vector<int> sequentialDigits(int low, int high) {
        vector<int> ans;
        string digits = "123456789";
        
        for(int len = 2; len <= 9; len++) {
            for(int start = 0; start <= 9 - len; start++) {
                int num = stoi(digits.substr(start, len));
                if(num >= low && num <= high) {
                    ans.push_back(num);
                }
            }
        }
        
        return ans;
    }
};


// using BFS ==> very common pattern for generating numbers with certain properties. Here, we generate sequential digits by starting with single-digit numbers and appending the next digit in sequence until we exceed the upper limit.
class Solution {
public:
   
    vector<int> sequentialDigits(int low, int high) {
        queue<int64_t> que; 
        for(int i=1; i<9; i++) {
            que.push(i);
        }
        vector<int> ans;
        while(!que.empty()) {
            int64_t ele = que.front();
            que.pop();
            
            if(ele >= low && ele <= high) {
                    ans.push_back(ele);
            }
            if(ele > high) break;

            int last_digit = ele % 10 ;

            if(last_digit + 1 <= 9) {
                int64_t final_digit = ele*10 + (last_digit+1) ;
                que.push(final_digit);
            }
        }

        return ans;

        
     }
};