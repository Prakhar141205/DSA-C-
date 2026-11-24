
class Solution {
public:

    // Euclidean Algorithm to calculate GCD
    long long GCD(long long a, long long b) {

        while (b != 0) {
            long long rem = a % b;
            a = b;
            b = rem;
        }

        return a;
    }

    // Calculate LCM using GCD
    long long LCM(long long a, long long b) {

        return (a / GCD(a, b)) * b;
    }

    int maxLength(vector<int>& nums) {

        int n = nums.size();
        int res = 0;

        for (int i = 0; i < n; i++) {

            long long prodVal = 1;
            long long gcdVal = 0;
            long long lcmVal = 1;

            for (int j = i; j < n; j++) {

                prodVal *= nums[j];

                gcdVal = GCD(gcdVal, nums[j]);

                lcmVal = LCM(lcmVal, nums[j]);

                if (prodVal == gcdVal * lcmVal) {
                    res = max(res, j - i + 1);
                }
            }
        }

        return res;
    }
};


// using cpp stl functions
class Solution {
public:
    int maxLength(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            long long prodVal = nums[i];
            long long gcdVal = nums[i];
            long long lcmVal = nums[i];
            for (int j = i + 1; j < nums.size(); j++) {
                prodVal = prodVal * nums[j];
                gcdVal = gcd(gcdVal, nums[j]);
                lcmVal = lcm(lcmVal, nums[j]);
                if (prodVal > gcdVal * lcmVal) {
                    break;
                }
                if (prodVal == gcdVal * lcmVal) {
                    res = max(res, j - i + 1);
                }
            }
        }

        return res;
    }
};