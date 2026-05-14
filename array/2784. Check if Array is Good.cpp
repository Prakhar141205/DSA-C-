class Solution {
public:
    bool isGood(vector<int>& nums) {
        int n = nums.size(), cnt = 1;
        if(n == 1) return 0;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n - 1; i++) {
            if(nums[i] != cnt++) return 0;
        }
        return nums[n - 1] == cnt - 1 && nums[n - 1] == nums[n - 2];
    }
};


class Solution {
 public:
  bool isGood(vector<int>& nums) {
    constexpr int kMax = 200;
    const int n = nums.size() - 1;
    vector<int> count(kMax + 1);

    for (const int num : nums)
      ++count[num];

    return all_of(count.begin() + 1, count.begin() + n, [](int c) {
      return c == 1;
    }) && count[n] == 2;
  }
};


class Solution {
public:
    bool isGood(vector<int>& nums) {
        ranges::sort(nums);
        if (nums[0] != 1 || nums.back() + 1 != nums.size()) {
            return false;
        }

        for (int i = 1; i + 1 < nums.size(); ++i) {
            if (nums[i] != nums[i - 1] + 1) {
                return false;
            }
        }

        return true;
    }
};