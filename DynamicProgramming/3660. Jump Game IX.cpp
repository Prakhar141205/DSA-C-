// can be done using graph and the dfs bfs
//  can be done using segment tree 



// using dynamic programming
class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();
        vector<int> preMax(n, INT_MIN);
        vector<int> sufMin(n, INT_MAX);
        vector<int> ans(n);

        // build a prefix array assuming there is only one condition 
        // cond 1 = where j < i is allowed only if nums[j] > nums[i].
        preMax[0] = nums[0]; 
        for(int i=1; i<n; ++i){
            preMax[i] = max(preMax[i-1], nums[i]);
        }

        // build a suffix  min array which contain the  min val after the i the index
        sufMin[n-1] = nums[n-1];
        for(int i=n-2; i>=0;--i){
            sufMin[i] = min(sufMin[i+1], nums[i]);
        }

        ans[n-1] = preMax[n-1]; // last index contains the preMax val because there is no option to go to further right

        for(int i=n-2; i>=0; --i){
            if(preMax[i] <= sufMin[i+1]){
                ans[i] = preMax[i];
            }else{ // preMax[i] >= sufMin[i+1]
                ans[i] = ans[i+1];
            }
        }

        return ans;
    }
};


class Solution {
public:
    struct Item {
        int value;
        int left;
        int right;
    };

    vector<int> maxValue(const vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 0);

        vector<Item> stack;

        for (int i = 0; i < n; ++i) {
            Item curr = {nums[i], i, i};

            while (!stack.empty() && stack.back().value > nums[i]) {
                Item top = stack.back();
                stack.pop_back();
                curr.value = max(curr.value, top.value);
                curr.left = top.left;
            }

            stack.push_back(curr);
        }

        for (size_t i = 0; i < stack.size(); ++i) {
            for (int j = stack[i].left; j <= stack[i].right; ++j) {
                ans[j] = stack[i].value;
            }
        }

        return ans;
    }
};


class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 0);

        // [value, index]
        using Item = pair<int, int>;
        vector<Item> prevMax(n);

        Item prev = {INT_MIN, -1};
        for (int i = 0; i < n; ++i) {
            if (nums[i] > prev.first) {
                prev = {nums[i], i};
            }
            prevMax[i] = prev;
        }

        auto process = [&](auto& self, int r, int rightMin,
                           int rightMax) -> void {
            auto [pMax, pivotIndex] = prevMax[r];
            int currMax = pMax <= rightMin ? pMax : rightMax;

            int nextRightMin = min(pMax, rightMin);
            for (int i = pivotIndex; i <= r; ++i) {
                ans[i] = currMax;
                nextRightMin = min(nextRightMin, nums[i]);
            }

            if (pivotIndex == 0) {
                return;
            }

            self(self, pivotIndex - 1, nextRightMin, currMax);
        };

        process(process, n - 1, INT_MAX, 0);

        return ans;
    }
};

class Solution {
public:
// with map tc >5.2%

    vector<int> maxValue(vector<int>& nums) {

        int n =nums.size();
        vector<int>pre(n,0);
        vector<int>vec(n);
        pre[0]=nums[0];
        vec[0]=nums[0];
        unordered_map<int,int>mpp;
        mpp[nums[0]]++;
        for(int i=1;i<n;i++){
            pre[i]=max(pre[i-1],nums[i]);
            vec[i]=nums[i];
            mpp[nums[i]]++;
        }
        sort(vec.rbegin(),vec.rend());
        vector<int>dp(n,0);
        int j=n-1;
        int m=1e9+7;
        int last=vec[0];
        for(int i=0;i<n && j>=0;i++){
            if(mpp[vec[i]]==0){
                continue;
            }
            int mi=1e9+7;
            while(j>=0 && nums[j]!=vec[i]){
                mpp[nums[j]]--;
                mi=min(mi,nums[j]);
                j--;
            }
            
            mi=min(mi,nums[j]);
            if(m<vec[i] && i!=0){
                vec[i]=last;
                dp[j]=vec[i];
            }
            else{
                dp[j]=vec[i];
            }
            last = dp[j];
            m=min(mi,m);
            mpp[nums[j]]--;
            j--;
        }
        for(int i=1;i<n;i++){
            dp[i]=max(dp[i-1],dp[i]);
        }
        return dp;

    


    }
};

typedef pair<int, int> pii;
class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int size = nums.size();
        vector<pii> stk;
        for (int i = 0; i < size; i++) {
            int maxVal = nums[i], cnt = 1;
            while (!stk.empty() && stk.back().first > nums[i]) {
                maxVal = max(maxVal, stk.back().first);
                cnt += stk.back().second;
                stk.pop_back();
            }
            stk.push_back({maxVal, cnt});
        }
        vector<int> res;
        res.reserve(size);
        for (auto [maxVal, cnt]: stk) {
            for (int i = 0; i < cnt; i++)
                res.push_back(maxVal);
        }
        return res;
    }
};
#pragma GCC optimize("Ofast,inline,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2")

#include <vector>
#include <algorithm>

using namespace std;

// Резервируем память один раз на все тесты
static int res_ptr[100005];

static const int fast_io = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class Solution {
public:
    vector<int> maxValue(vector<int>& a) {
        const int n = a.size();
        if (__builtin_expect(n == 0, 0)) return {};
        
        // Префиксный максимум (разворачиваем цикл через прагму)
        res_ptr[0] = a[0];
        #pragma GCC ivdep
        for (int i = 1; i < n; ++i) {
            res_ptr[i] = (a[i] > res_ptr[i - 1]) ? a[i] : res_ptr[i - 1];
        }

        // Суффиксный минимум + логика наследования
        int cur_min = a[n - 1];
        #pragma GCC ivdep
        for (int i = n - 2; i >= 0; --i) {
            // Если pre_max > min_справа, берем готовый ответ соседа
            if (res_ptr[i] > cur_min) {
                res_ptr[i] = res_ptr[i + 1];
            }
            // Ветвление для минимума через тернарник (меньше ветвлений для CPU)
            cur_min = (a[i] < cur_min) ? a[i] : cur_min;
        }
        
        // Максимально быстрый возврат через выделение памяти под размер
        vector<int> out(n);
        copy(res_ptr, res_ptr + n, out.begin());
        return out;
    }
};

class Solution {
public:
    static vector<int> maxValue(vector<int>& nums) {
        const int n=nums.size();
        vector<int> prefMax(n), sufMin(n);
        prefMax[0]=nums[0];
        sufMin[n-1]=nums[n-1];

        for(int i=1; i<n; i++){
            const int x=nums[i], y=nums[n-1-i];
            prefMax[i]=max(prefMax[i-1], x);
            sufMin[n-1-i]=min(sufMin[n-i], y);
        }
        vector<int> ans(n);
        ans[n-1]=prefMax[n-1];
        for(int i=n-2; i>=0; i--){
            if (prefMax[i]>sufMin[i+1]) 
                ans[i]=max(prefMax[i], ans[i+1]);
            else ans[i]=prefMax[i];
        }
        return ans;
    }
};