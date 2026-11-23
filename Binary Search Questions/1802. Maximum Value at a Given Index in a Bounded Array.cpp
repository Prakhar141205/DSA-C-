class Solution {
public:
    int maxValue(int n, int index, int maxSum) {
        int ans = 1;

        for (int x = 1; x <= maxSum; x++) {
            long long sum = x;

            // Calculate minimum sum on the left side
            int val = x - 1;

            for (int i = index - 1; i >= 0; i--) {
                sum += max(1, val);
                val--;
            }

            // Calculate minimum sum on the right side
            val = x - 1;

            for (int i = index + 1; i < n; i++) {
                sum += max(1, val);
                val--;
            }

            if (sum <= maxSum) {
                ans = x;
            } else {
                break;
            }
        }

        return ans;
    }
};


class Solution {
public:
    long long calculate(int peak, int len) {
        if (peak > len) {
            return 1LL * (peak - 1 + peak - len) * len / 2;
        }

        return 1LL * peak * (peak - 1) / 2 + (len - peak + 1);
    }

    int maxValue(int n, int index, int maxSum) {

        for (int x = maxSum; x >= 1; x--) {

            long long left = calculate(x, index);
            long long right = calculate(x, n - index - 1);

            long long total = left + right + x;

            if (total <= maxSum) {
                return x;
            }
        }

        return 1;
    }
};

// most optimal TC O(log(maxSum)) and SC O(1)
class Solution {
public:
    typedef long long ll;

    // Calculates the sum of 'cnt' elements:
    // x-1, x-2, x-3, ..., x-cnt
    //
    // Using the arithmetic progression formula:
    // Sum = cnt*x - cnt*(cnt+1)/2
    ll getSumByFormula(ll cnt, ll x) {
        return cnt * x - (cnt * (cnt + 1)) / 2;
    }

    int maxValue(int n, int index, int maxSum) {

        // Binary search for the maximum possible value at nums[index]
        int l = 1;
        int r = maxSum;

        ll mid_val;
        ll res = 0;

        while (l <= r) {

            // Calculate the middle value (candidate answer)
            mid_val = l + (r - l) / 2;

            // -----------------------------------------
            // Calculate minimum sum required on LEFT
            // -----------------------------------------

            // Number of elements that can decrease from mid_val
            // before reaching 1.
            // We cannot have more elements than 'index'.
            ll left_cnt = min((ll)index, mid_val - 1);

            // Sum of decreasing elements:
            // mid_val-1, mid_val-2, ..., mid_val-left_cnt
            ll left_sum = getSumByFormula(left_cnt, mid_val);

            // Remaining positions must contain 1,
            // because array elements must be positive.
            left_sum += max(0LL, (ll)index - (mid_val - 1));

            // -----------------------------------------
            // Calculate minimum sum required on RIGHT
            // -----------------------------------------

            // Number of elements that can decrease from mid_val
            // before reaching 1.
            ll right_cnt = min((ll)n - index - 1, mid_val - 1);

            // Sum of decreasing elements on the right.
            ll right_sum = getSumByFormula(right_cnt, mid_val);

            // Remaining positions must contain 1.
            right_sum += max(0LL, (ll)(n - index - 1) - (mid_val - 1));

            // -----------------------------------------
            // Calculate total minimum array sum
            // -----------------------------------------

            // Include:
            // 1. Left side sum
            // 2. nums[index] itself
            // 3. Right side sum
            ll total_sum = left_sum + mid_val + right_sum;

            // -----------------------------------------
            // Binary Search Decision
            // -----------------------------------------

            if (total_sum <= maxSum) {

                // Current value is possible.
                // Store it as a potential answer.
                res = max(res, mid_val);

                // Try a larger value.
                l = mid_val + 1;

            } else {

                // Current value requires too much sum.
                // Try a smaller value.
                r = mid_val - 1;
            }
        }

        return res;
    }
};