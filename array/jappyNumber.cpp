class Solution {
public:
    int fun(int n){
        int sum =0;
        while(n >0){
            int d = n%10;
            n = n/10;
            sum = sum + d*d;
        }
        return sum;
    }
    bool isHappy(int n) {
        int slow = n;
        int fast=n;
        while(fast != 1){
            slow = fun(slow);
            fast = fun(fast);
            fast = fun(fast);
            if(slow == fast && slow != 1){
                return false ;
            }

        }
        fast = 1;
        return true;
    }
};


// Approach 2

class Solution {
public:
    bool isHappy(int n) {
        
        while(n!=1 && n!=4)
        {
            int ans=0;
        while(n)
        {
            int digits=n%10;
            ans+=digits*digits;
            n=n/10;
        }
            n=ans;
        }
        return n==1;
        
    }
};

// Approach 3

class Solution {
public:
    bool isHappy(int n) {
        auto next = [](int n)->int{
            int sum = 0;
            while(n){
                int x = n % 10;
                sum += x * x;
                n /= 10;
            }
            return sum;
        };
        unordered_set<int> st;
        while(n != 1){
            if(st.count(n)) return false; 
            st.insert(n);
            n = next(n);
        }

        return true;
    }
};