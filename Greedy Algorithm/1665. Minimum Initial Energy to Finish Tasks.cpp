class Solution {
 public:
  int minimumEffort(vector<vector<int>>& tasks) {
    int ans = 0;
    int prevSaved = 0;

    ranges::sort(tasks, ranges::greater{},
                 [](const vector<int>& task) { return task[1] - task[0]; });

    for (const vector<int>& task : tasks) {
      const int actual = task[0];
      const int minimum = task[1];
      if (prevSaved < minimum) {
        ans += minimum - prevSaved;
        prevSaved = minimum - actual;
      } else {
        prevSaved -= actual;
      }
    }

    return ans;
  }
};


class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        // 1. 依照 (minimum - actual) 的差值進行降序排序
        sort(tasks.begin(), tasks.end(), [](const vector<int>& a, const vector<int>& b) {
            return (a[1] - a[0]) > (b[1] - b[0]);
        });

        int res = 0;        // 所需的最小初始能量
        int sumActual = 0;  // 累計消耗的能量

        // 2. 依序處理排序後的任務
        for (const auto& task : tasks) {
            int actual = task[0];
            int minimum = task[1];
            
            // 執行此任務時，初始能量至少要能支撐：
            // (之前任務的總消耗) + (當前任務的啟動門檻)
            res = max(res, sumActual + minimum);
            
            // 更新目前總消耗
            sumActual += actual;
        }

        return res;
    }
};

class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        int m = tasks.size();
        ranges::sort(tasks, {}, [](auto& p) {return p[1] - p[0];});
        int curr = 0;
        for (int j = 0;j < m;++j) {
            curr = max(tasks[j][1], curr + tasks[j][0]);
        }
        return curr;
    }
};