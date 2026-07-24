class Solution {
public:
  int uniqueXorTriplets(vector<int>& nums) {
    int n = static_cast<int>(nums.size());

    if (n <= 2) {
      return n;
    }

    return 1 << __lg(n) + 1;
  }
};

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();

        if(n <= 2 ) return n;

        int ans = 1;
        while(ans <= n) {
            ans <<= 1;
        }

        return ans;
    }
};