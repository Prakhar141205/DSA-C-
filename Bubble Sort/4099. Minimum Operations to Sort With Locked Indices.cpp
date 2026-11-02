class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& locked, int k) {
        int n = nums.size();
        int ops = 0, reqK = 0;
        for(int i=0; i<n; i++) {

            for(int j=0; j<n-1; j++) {

                if(nums[j] > nums[j+1]) {

                    if(locked[j]) {
                        locked[j] = 0;
                        reqK++;
                    }

                    if(locked[j+1]) {
                        locked[j+1] = 0;
                        reqK++;
                    }

                    swap(nums[j], nums[j+1]);
                    ops++;
                }
            }
        }

        if(reqK > k) return -1;
        return ops+reqK;
    }
};


class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& locked, int k) {
        int n = nums.size();
        int mx = -1;
        int sol = 0;
        for(int i = 0; i < n ;i++){
            mx = max(nums[i], mx);
            if(locked[i] == 1){
                if(!(nums[i] == i+1 && mx == i + 1)){
                    sol++;
                }
            }
        }
        if(sol > k){
            return -1;
        }
        for(int i = 0;i < n; i++){
            for(int j = i + 1; j < n; j++){
                if(nums[i] > nums[j]){
                    sol++;
                }
            }
        }
        return sol;
    }
};



/*
 LeetCode 4099 — Minimum Operations to Sort With Locked Indices
 Approaches:
 1) Brute force all unlock subsets: O(2^m * n^2), m = locked positions.
 2) Cycle intervals + quadratic inversion count: O(n^2).
 3) Cycle intervals + Fenwick inversion count: O(n log n), recommended.
 4) Cycle intervals + merge-sort inversion count: O(n log n).
 5) DSU cycle components + Fenwick inversion count: O(n log n).

 Key theorem:
 A permutation position maps i -> nums[i]-1. Every non-trivial cycle must be
 contained in one contiguous unlocked component. Thus, for each non-trivial
 cycle, every index in [minimum cycle index, maximum cycle index] must be
 unlocked. The union of these intervals gives the minimum required unlock set.

 The minimum adjacent swaps are exactly the inversion count of nums.
 Answer = inversion_count + required_locked_positions, unless required > k.
*/

#include <algorithm>
#include <climits>
#include <numeric>
#include <vector>
using namespace std;

class FenwickTree {
    int n;
    vector<int> bit;
public:
    explicit FenwickTree(int n) : n(n), bit(n + 1, 0) {}
    void add(int i) {
        for (; i <= n; i += i & -i) ++bit[i];
    }
    int sum(int i) const {
        int ans = 0;
        for (; i > 0; i -= i & -i) ans += bit[i];
        return ans;
    }
};

static long long inversionsFenwick(const vector<int>& nums) {
    int n = (int)nums.size();
    FenwickTree fw(n);
    long long ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        ans += fw.sum(nums[i] - 1);
        fw.add(nums[i]);
    }
    return ans;
}

static vector<char> cycleRequiredIntervals(const vector<int>& nums) {
    int n = (int)nums.size();
    vector<char> seen(n, false), required(n, false);
    vector<int> diff(n + 1, 0);

    for (int start = 0; start < n; ++start) {
        if (seen[start]) continue;
        int x = start, len = 0, lo = n, hi = -1;
        while (!seen[x]) {
            seen[x] = true;
            ++len;
            lo = min(lo, x);
            hi = max(hi, x);
            x = nums[x] - 1;
        }
        if (len > 1) {
            ++diff[lo];
            --diff[hi + 1];
        }
    }

    int active = 0;
    for (int i = 0; i < n; ++i) {
        active += diff[i];
        required[i] = active > 0;
    }
    return required;
}

static long long requiredUnlockCount(
    const vector<int>& locked, const vector<char>& required
) {
    long long ans = 0;
    for (int i = 0; i < (int)locked.size(); ++i)
        if (locked[i] == 1 && required[i]) ++ans;
    return ans;
}

// 1. Exhaustive unlock-subset baseline. Only feasible for tiny m.
class SolutionBruteForceUnlockSubsets {
public:
    int minOperations(vector<int>& nums, vector<int>& locked, int k) {
        int n = (int)nums.size();
        vector<int> positions;
        for (int i = 0; i < n; ++i)
            if (locked[i]) positions.push_back(i);

        int m = (int)positions.size();
        if (m >= 63) return -1; // avoid invalid/absurd subset enumeration

        vector<char> unlocked(n, false);
        for (int i = 0; i < n; ++i) unlocked[i] = (locked[i] == 0);

        long long best = LLONG_MAX;
        unsigned long long total = 1ULL << m;

        for (unsigned long long mask = 0; mask < total; ++mask) {
            int unlockCost = __builtin_popcountll(mask);
            if (unlockCost > k || unlockCost >= best) continue;

            for (int b = 0; b < m; ++b)
                if (mask & (1ULL << b)) unlocked[positions[b]] = true;

            bool ok = true;
            long long swaps = 0;
            int l = 0;

            while (l < n && ok) {
                if (!unlocked[l]) {
                    if (nums[l] != l + 1) ok = false;
                    ++l;
                    continue;
                }

                int r = l, mn = nums[l], mx = nums[l];
                while (r + 1 < n && unlocked[r + 1]) {
                    ++r;
                    mn = min(mn, nums[r]);
                    mx = max(mx, nums[r]);
                }

                if (mn != l + 1 || mx != r + 1) {
                    ok = false;
                    break;
                }

                for (int i = l; i <= r; ++i)
                    for (int j = i + 1; j <= r; ++j)
                        if (nums[i] > nums[j]) ++swaps;

                l = r + 1;
            }

            if (ok) best = min(best, (long long)unlockCost + swaps);

            for (int b = 0; b < m; ++b)
                if (mask & (1ULL << b)) unlocked[positions[b]] = false;
        }

        return best == LLONG_MAX ? -1 : (int)best;
    }
};

// 2. Cycle interval characterization + O(n^2) inversion counting.
class SolutionCycleIntervalsQuadratic {
public:
    int minOperations(vector<int>& nums, vector<int>& locked, int k) {
        auto required = cycleRequiredIntervals(nums);
        long long unlocks = requiredUnlockCount(locked, required);
        if (unlocks > k) return -1;

        long long inv = 0;
        int n = (int)nums.size();
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (nums[i] > nums[j]) ++inv;

        return (int)(unlocks + inv);
    }
};

// 3. Recommended O(n log n): cycle intervals + Fenwick inversion count.
class SolutionOptimalFenwick {
public:
    int minOperations(vector<int>& nums, vector<int>& locked, int k) {
        auto required = cycleRequiredIntervals(nums);
        long long unlocks = requiredUnlockCount(locked, required);
        if (unlocks > k) return -1;
        return (int)(unlocks + inversionsFenwick(nums));
    }
};

// Merge-sort inversion counter for Approach 4.
static long long mergeCount(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (l >= r) return 0;
    int mid = l + (r - l) / 2;
    long long ans = mergeCount(a, tmp, l, mid)
                  + mergeCount(a, tmp, mid + 1, r);
    int i = l, j = mid + 1, w = l;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) tmp[w++] = a[i++];
        else {
            tmp[w++] = a[j++];
            ans += mid - i + 1;
        }
    }
    while (i <= mid) tmp[w++] = a[i++];
    while (j <= r) tmp[w++] = a[j++];
    for (int p = l; p <= r; ++p) a[p] = tmp[p];
    return ans;
}

static long long inversionsMergeSort(const vector<int>& nums) {
    if (nums.empty()) return 0;
    vector<int> a = nums, tmp(nums.size());
    return mergeCount(a, tmp, 0, (int)a.size() - 1);
}

// 4. Alternative O(n log n): cycle intervals + merge-sort inversions.
class SolutionOptimalMergeSort {
public:
    int minOperations(vector<int>& nums, vector<int>& locked, int k) {
        auto required = cycleRequiredIntervals(nums);
        long long unlocks = requiredUnlockCount(locked, required);
        if (unlocks > k) return -1;
        return (int)(unlocks + inversionsMergeSort(nums));
    }
};

// DSU helper for Approach 5.
class DSU {
    vector<int> parent, sz;
public:
    explicit DSU(int n) : parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }
};

// 5. Alternative cycle discovery with DSU + Fenwick inversions.
class SolutionDSUFenwick {
public:
    int minOperations(vector<int>& nums, vector<int>& locked, int k) {
        int n = (int)nums.size();
        DSU dsu(n);
        for (int i = 0; i < n; ++i) dsu.unite(i, nums[i] - 1);

        vector<int> lo(n, n), hi(n, -1), sz(n, 0);
        for (int i = 0; i < n; ++i) {
            int r = dsu.find(i);
            lo[r] = min(lo[r], i);
            hi[r] = max(hi[r], i);
            ++sz[r];
        }

        vector<int> diff(n + 1, 0);
        for (int r = 0; r < n; ++r) {
            if (sz[r] > 1) {
                ++diff[lo[r]];
                --diff[hi[r] + 1];
            }
        }

        long long unlocks = 0;
        int active = 0;
        for (int i = 0; i < n; ++i) {
            active += diff[i];
            if (active > 0 && locked[i] == 1) ++unlocks;
        }
        if (unlocks > k) return -1;
        return (int)(unlocks + inversionsFenwick(nums));
    }
};

/*
Paste this class into LeetCode as class Solution:

class Solution {
    struct BIT {
        int n; vector<int> bit;
        BIT(int n) : n(n), bit(n + 1, 0) {}
        void add(int i) { for (; i <= n; i += i & -i) ++bit[i]; }
        int query(int i) {
            int s = 0;
            for (; i > 0; i -= i & -i) s += bit[i];
            return s;
        }
    };
public:
    int minOperations(vector<int>& nums, vector<int>& locked, int k) {
        int n = nums.size();
        vector<char> seen(n, false);
        vector<int> diff(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            if (seen[i]) continue;
            int x = i, len = 0, lo = n, hi = -1;
            while (!seen[x]) {
                seen[x] = true; ++len;
                lo = min(lo, x); hi = max(hi, x);
                x = nums[x] - 1;
            }
            if (len > 1) { ++diff[lo]; --diff[hi + 1]; }
        }

        long long unlocks = 0;
        int active = 0;
        for (int i = 0; i < n; ++i) {
            active += diff[i];
            if (active > 0 && locked[i] == 1) ++unlocks;
        }
        if (unlocks > k) return -1;

        BIT bit(n);
        long long inv = 0;
        for (int i = n - 1; i >= 0; --i) {
            inv += bit.query(nums[i] - 1);
            bit.add(nums[i]);
        }
        return (int)(unlocks + inv);
    }
};

Examples:
1) nums=[2,1,3,4], locked=[0,1,0,1], k=1:
   cycle (0,1), required interval [0,1], unlock count 1,
   inversion count 1, answer 2.
2) nums=[3,1,2], locked=[1,0,1], k=2:
   3-cycle span [0,2], unlock count 2, inversion count 2, answer 4.
3) nums=[2,3,1], locked=[1,0,0], k=0:
   3-cycle span [0,2], one required locked position but k=0, answer -1.

Important: a correctly placed index can still need unlocking if it lies inside
the span of a non-trivial cycle. Do not unlock only misplaced positions.
*/
