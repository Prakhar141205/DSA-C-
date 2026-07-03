class Solution {
public:
    /* 
     number of 1's bit in binary representation 
     an even number and its half has same number of 1 bits
     while an odd number has bits more than one half of the number
    */
    int hammingWeight(uint32_t n) {
        int count = 0;
        while(n) {
            count += (n & 1);
            n >>= 1;
        }
        return count;
    }
};

// using Brian Kernighan’s Algorithm
// or get the last set bit and remove it from the number, repeat until the number becomes 0
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        while(n) {
            n = n & (n-1);
            count++;
        }
        return count;
    }
};

// using Modulo and Division


class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        while(n) {
            count += (n%2);
            n /= 2;
        }
        return count;
    }
};  


// using built-in function
class Solution {
public:
    int hammingWeight(uint32_t n) {
        

        return __builtin_popcount(n);
    }
};  


// finding the ith big and checking if it is set or not
class Solution {
public:             
    int hammingWeight(uint32_t n) {
        int count = 0;
       for(int i=31; i>=0; i--) {
            if(n & (1<<i)) count++;
        }
        return count;
    }
};