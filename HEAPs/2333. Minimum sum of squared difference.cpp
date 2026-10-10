class Solution {
public:
    typedef long long ll;
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        int tK = k1 + k2 ;

        priority_queue<ll> pq; // pushing all the diff in the maxHeap
        for(int i=0; i<n1; i++) {
            pq.push(abs(nums1[i] - nums2[i]));
        }

        while(tK > 0 && !pq.empty()) {
            ll maxDiff = pq.top();
            pq.pop();

            if(maxDiff == 0) break;
            maxDiff -= 1;

            pq.push(maxDiff);
            tK--;

        }

        ll ans = 0;
        while(!pq.empty()) {
            ll d = pq.top();
            pq.pop();

            ans += d * d;
        }
        return ans;
    }
};

// Using Binary search to find the minimum sum of squared differences
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1,
                               int k2) {
        int n = nums1.size();
        long long ans = 0;
        int k = k1 + k2;
        int maxDif = 0;
        int res = 0;
        for (int i = 0; i < n; i++) {
            nums1[i] = abs(nums1[i] - nums2[i]);
            maxDif = max(maxDif, nums1[i]);
        }
        int l = 0, r = maxDif;
        auto check = [&](int mid) -> bool {
            long long sum = 0;
            for (int num : nums1) {
                sum += num > mid ? num - mid : 0;
            }
            return sum <= k;
        };
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                r = mid - 1;
                res = mid;
            } else {
                l = mid + 1;
            }
        }
        for (int i = 0; i < n; i++) {
            if (nums1[i] > res) {
                k -= (nums1[i] - res);
            }
        }
        sort(nums1.begin(), nums1.end(), greater<int>());
        for (int num : nums1) {
            long long diff = res >= num ? num : res;
            if (k && diff) {
                diff--;
                k--;
            }
            ans += diff * diff;
        }
        return ans;
    }
};

// Greedy approach to find the minimum sum of squared differences
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1,
                               int k2) {
        long long k = (long long)k1 + k2;
        int n = nums1.size();
        for (int i = 0; i < n; i++) {
            nums1[i] = abs(nums1[i] - nums2[i]);
        }
        if (accumulate(nums1.begin(), nums1.end(), 0LL) <= k) {
            return 0;
        }
        sort(nums1.begin(), nums1.end(), greater<int>());
        nums1.push_back(0);
        for (int i = 1; i <= n; i++) {
            long long cost = (long long)(nums1[i - 1] - nums1[i]) * i;
            if (cost > k) {
                long long q = k / i, r = k % i;
                long long hi = nums1[i - 1] - q;
                long long ans = hi * hi * (i - r) + (hi - 1) * (hi - 1) * r;
                for (int j = i; j < n; j++) {
                    ans += (long long)nums1[j] * nums1[j];
                }
                return ans;
            }
            k -= cost;
        }
        return 0;
    }
};