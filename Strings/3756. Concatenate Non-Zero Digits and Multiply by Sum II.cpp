const int MOD = 1e9 + 7;
const int MAX_N = 100001;
long long pow10[MAX_N];

// init runs only once for all test cases
int init = []() {
    pow10[0] = 1;
    for (int i = 1; i < MAX_N; ++i) {
        pow10[i] = (pow10[i - 1] * 10) % MOD;
    }
    return 0;
}();

class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();
        vector<int> sum(n + 1, 0);
        vector<long long> x(n + 1, 0);
        vector<int> cnt(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            int d = s[i] - '0';
            sum[i + 1] = sum[i] + d;
            x[i + 1] = (d > 0) ? (x[i] * 10 + d) % MOD : x[i];
            cnt[i + 1] = cnt[i] + (d > 0);
        }
        int m = queries.size();
        vector<int> res(m, 0);
        for (int i = 0; i < m; ++i) {
            int l = queries[i][0];
            int r = queries[i][1] + 1;
            int length = cnt[r] - cnt[l];
            long long val_x = (x[r] - x[l] * pow10[length] % MOD + MOD) % MOD;
            long long val_sum = sum[r] - sum[l];
            res[i] = (val_x * val_sum) % MOD;
        }
        return res;
    }
};

// Another implementation with O(n) preprocessing and O(1) query time
class Solution {
public:
    int MOD = 1e9+7;
    typedef long long ll;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.length();

        vector<int> nonZeroCount(n, 0);    // non-zero digits count in s[0..i]
        vector<ll> numberUpTo(n, 0);      // number formed from non-zero digits in s[0..i]
        vector<ll> digitSumUpTo(n, 0);    // digit sum of s[0..i]
        vector<ll> pow10(n + 1, 0);  // 10^i

        pow10[0] = 1;
        for (int i = 1; i <= n; i++)
            pow10[i] = (pow10[i - 1] * 10) % MOD;


        nonZeroCount[0]      = (s[0] != '0') ? 1 : 0;
        numberUpTo[0]   = s[0] - '0';
        digitSumUpTo[0] = s[0] - '0';

        for (int i = 1; i < n; i++) {
            int digit = s[i] - '0';
            nonZeroCount[i] = nonZeroCount[i - 1] + (digit != 0 ? 1 : 0);
        }

        for (int i = 1; i < n; i++) {
            int digit = s[i] - '0';
            if (digit != 0)
                numberUpTo[i] = (numberUpTo[i - 1] * 10 + digit) % MOD;
            else
                numberUpTo[i] = numberUpTo[i - 1];
        }

        for (int i = 1; i < n; i++) {
            digitSumUpTo[i] = digitSumUpTo[i - 1] + (s[i] - '0');
        }

        int q = queries.size();
        vector<int> result(q);

        for (int i = 0; i < q; i++) {
            int l  = queries[i][0];
            int r = queries[i][1];

            int startCount = (l == 0) ? 0 : nonZeroCount[l - 1];
            ll numBefore   = (l == 0) ? 0 : numberUpTo[l - 1];

            int endCount = nonZeroCount[r];
            int subStrLen = endCount - startCount;

            if (subStrLen == 0) {
                result[i] = 0;
                continue;
            }

            ll x   = (numberUpTo[r] - (numBefore * pow10[subStrLen] % MOD) + MOD) % MOD;
            ll sum = digitSumUpTo[r] - ((l == 0) ? 0 : digitSumUpTo[l - 1]);

            result[i] = (int)((x * sum) % MOD);
        }

        return result;
    }
};