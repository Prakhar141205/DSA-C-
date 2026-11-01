/*
LeetCode 991 — Broken Calculator
Comprehensive C++ solution variations

Operations in the forward direction:
1. x -> 2*x
2. x -> x-1

Goal: minimum operations to transform startValue into target.

IMPORTANT MATHEMATICAL INSIGHT
It is easier to work BACKWARD from target to startValue.

Reverse operations:
1. If x is even, undo a doubling: x -> x/2.
2. Undo a subtraction: x -> x+1.

Optimal reverse greedy:
- If x <= startValue, add startValue - x operations (only incrementing in
  reverse, corresponding to subtracting in the forward direction).
- If x > startValue and x is odd, increment it once to make it even.
- If x > startValue and x is even, divide it by 2.
Repeat until x <= startValue.

Why this is optimal:
- For an odd x > startValue, halving is not a valid reverse operation.
  The only useful reverse choice is x+1.
- For an even x > startValue, halving removes a forward doubling. Choosing
  x+1 instead cannot improve the route: it increases the value and requires
  at least as much work before a later halving. The exchange argument leads
  to halving immediately.
- Once x <= startValue, reverse increments are the only useful way to reach
  startValue; in forward direction this is simply subtracting.

Included solution variations:
1. Forward BFS — shortest path on an unweighted state graph (small values only).
2. Forward Dijkstra — same state graph, unnecessary for unit edge weights.
3. Forward DFS/backtracking — exhaustive search, small values only.
4. Forward memoized DFS with bounded state range — small values only.
5. Reverse BFS — shortest path using predecessor edges (small values only).
6. Reverse recursive greedy — O(log target) time.
7. Reverse iterative greedy — O(log target) time, O(1) space.
8. Reverse greedy using a loop with operation counter and early target<=start.
9. Reverse greedy using bit/parity reasoning — equivalent implementation.

The problem's constraints go up to 10^9. Use #7/#8/#9 in production/interviews.
BFS/DFS approaches are educational and cannot handle the maximum constraints.
*/

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------------------------------------
// 1. FORWARD BFS
// State x has outgoing edges x -> 2*x and x -> x-1.
// All edges have unit cost, so BFS finds the minimum number of operations.
//
// To keep the graph finite for demonstration, only explore values in
// [1, upperBound], where upperBound = max(startValue, 2*target).
// Intended only for small values; state count can be very large.
// Time/space: O(number of explored states).
// -----------------------------------------------------------------------------
class Solution1_ForwardBFS {
public:
    int brokenCalc(int startValue, int target) {
        if (startValue >= target) return startValue - target;

        long long upperBound = 2LL * target;
        queue<pair<long long, int>> q;
        unordered_set<long long> visited;

        q.push({startValue, 0});
        visited.insert(startValue);

        while (!q.empty()) {
            auto [x, steps] = q.front();
            q.pop();

            if (x == target) return steps;

            long long doubled = 2LL * x;
            if (doubled <= upperBound && visited.insert(doubled).second) {
                q.push({doubled, steps + 1});
            }

            long long decreased = x - 1;
            if (decreased >= 1 && visited.insert(decreased).second) {
                q.push({decreased, steps + 1});
            }
        }

        return -1;
    }
};

// -----------------------------------------------------------------------------
// 2. FORWARD DIJKSTRA
// Treat each operation as an edge of cost 1 and use a min-priority queue.
// Dijkstra is correct, but BFS is simpler and faster because all edge weights
// are identical. Also intended only for small values.
// -----------------------------------------------------------------------------
class Solution2_ForwardDijkstra {
public:
    int brokenCalc(int startValue, int target) {
        if (startValue >= target) return startValue - target;

        long long upperBound = 2LL * target;
        using State = pair<int, long long>; // distance, displayed value

        priority_queue<State, vector<State>, greater<State>> pq;
        unordered_map<long long, int> dist;

        dist[startValue] = 0;
        pq.push({0, startValue});

        while (!pq.empty()) {
            auto [d, x] = pq.top();
            pq.pop();

            if (dist[x] != d) continue;
            if (x == target) return d;

            long long nextValues[2] = {2LL * x, x - 1};

            for (long long nx : nextValues) {
                if (nx < 1 || nx > upperBound) continue;

                if (!dist.count(nx) || d + 1 < dist[nx]) {
                    dist[nx] = d + 1;
                    pq.push({d + 1, nx});
                }
            }
        }

        return -1;
    }
};

// -----------------------------------------------------------------------------
// 3. FORWARD DFS / BACKTRACKING
// Explore all operation sequences up to a depth limit and keep the shortest.
// This is exponential and is included only to demonstrate brute force.
// A finite bound and depth limit are necessary to prevent unbounded exploration.
// -----------------------------------------------------------------------------
class Solution3_ForwardDFS {
    int answer;
    long long upperBound;

    void dfs(long long x, int steps, int target, int depthLimit) {
        if (steps >= answer || steps > depthLimit) return;
        if (x == target) {
            answer = steps;
            return;
        }

        if (x < 1 || x > upperBound) return;

        // Doubling
        if (2LL * x <= upperBound) {
            dfs(2LL * x, steps + 1, target, depthLimit);
        }

        // Subtract one
        if (x > 1) {
            dfs(x - 1, steps + 1, target, depthLimit);
        }
    }

public:
    int brokenCalc(int startValue, int target) {
        if (startValue >= target) return startValue - target;

        answer = INT_MAX;
        upperBound = 2LL * target;
        int depthLimit = 2 * target; // Small-input teaching bound only.
        dfs(startValue, 0, target, depthLimit);

        return answer == INT_MAX ? -1 : answer;
    }
};

// -----------------------------------------------------------------------------
// 4. FORWARD MEMOIZED DFS WITH A BOUNDED STATE RANGE
// Find shortest distances recursively from startValue to each reachable value.
// Since this is a cyclic graph (subtracting and doubling can revisit states),
// use a distance-relaxation / memo table carefully. This bounded teaching
// version uses BFS-like relaxation and is not recommended over #1.
// -----------------------------------------------------------------------------
class Solution4_ForwardBoundedRelaxation {
public:
    int brokenCalc(int startValue, int target) {
        if (startValue >= target) return startValue - target;

        int upperBound = 2 * target;
        const int INF = INT_MAX / 2;
        vector<int> dist(upperBound + 1, INF);
        queue<int> q;

        dist[startValue] = 0;
        q.push(startValue);

        while (!q.empty()) {
            int x = q.front();
            q.pop();

            if (x == target) return dist[x];

            int a = 2 * x;
            if (a <= upperBound && dist[a] > dist[x] + 1) {
                dist[a] = dist[x] + 1;
                q.push(a);
            }

            int b = x - 1;
            if (b >= 1 && dist[b] > dist[x] + 1) {
                dist[b] = dist[x] + 1;
                q.push(b);
            }
        }

        return -1;
    }
};

// -----------------------------------------------------------------------------
// 5. REVERSE BFS
// Reverse edges from x are:
// - x -> x+1 (undo a forward decrement)
// - x -> x/2 when x is even (undo a forward doubling)
//
// BFS explores predecessors from target until startValue is reached.
// Bound values to [1, 2*target + 1] for this small-input reference approach.
// -----------------------------------------------------------------------------
class Solution5_ReverseBFS {
public:
    int brokenCalc(int startValue, int target) {
        if (target <= startValue) return startValue - target;

        long long upperBound = 2LL * target + 1;
        queue<pair<long long, int>> q;
        unordered_set<long long> visited;

        q.push({target, 0});
        visited.insert(target);

        while (!q.empty()) {
            auto [x, steps] = q.front();
            q.pop();

            if (x == startValue) return steps;

            long long plusOne = x + 1;
            if (plusOne <= upperBound &&
                visited.insert(plusOne).second) {
                q.push({plusOne, steps + 1});
            }

            if (x % 2 == 0) {
                long long half = x / 2;
                if (half >= 1 && visited.insert(half).second) {
                    q.push({half, steps + 1});
                }
            }
        }

        return -1;
    }
};

// -----------------------------------------------------------------------------
// 6. REVERSE RECURSIVE GREEDY
// Recurrence:
// f(x) = startValue - x, if x <= startValue
// f(x) = 1 + f(x+1), if x > startValue and x is odd
// f(x) = 1 + f(x/2), if x > startValue and x is even
//
// Time: O(log target) because odd values are increased once and then halved.
// Space: O(log target) recursion stack.
// -----------------------------------------------------------------------------
class Solution6_ReverseRecursive {
    int solve(long long x, int startValue) {
        if (x <= startValue) {
            return startValue - (int)x;
        }

        if (x % 2 == 1) {
            return 1 + solve(x + 1, startValue);
        }

        return 1 + solve(x / 2, startValue);
    }

public:
    int brokenCalc(int startValue, int target) {
        return solve(target, startValue);
    }
};

// -----------------------------------------------------------------------------
// 7. REVERSE ITERATIVE GREEDY — CANONICAL OPTIMAL SOLUTION
// Time: O(log target), Space: O(1).
// -----------------------------------------------------------------------------
class Solution7_ReverseIterative {
public:
    int brokenCalc(int startValue, int target) {
        int operations = 0;

        while (target > startValue) {
            if (target % 2 == 1) {
                ++target;       // Reverse a forward decrement.
            } else {
                target /= 2;    // Reverse a forward doubling.
            }
            ++operations;
        }

        return operations + (startValue - target);
    }
};

// -----------------------------------------------------------------------------
// 8. REVERSE ITERATIVE GREEDY WITH EARLY CASE
// If startValue >= target, only subtract-one operations are useful.
// Otherwise apply reverse parity logic.
// Same O(log target) time and O(1) space.
// -----------------------------------------------------------------------------
class Solution8_ReverseGreedyEarlyCase {
public:
    int brokenCalc(int startValue, int target) {
        if (startValue >= target) {
            return startValue - target;
        }

        int steps = 0;
        while (target > startValue) {
            if (target & 1) {
                target += 1;
            } else {
                target >>= 1;
            }
            ++steps;
        }

        return steps + startValue - target;
    }
};

// -----------------------------------------------------------------------------
// 9. REVERSE GREEDY USING A LONG LONG STATE
// This is defensive against overflow if constraints are changed. For the
// original constraints, int is sufficient because target <= 1e9 and the
// reverse odd adjustment can reach at most 1e9 + 1.
// Time: O(log target), Space: O(1).
// -----------------------------------------------------------------------------
class Solution9_ReverseGreedyLongLong {
public:
    int brokenCalc(int startValue, int target) {
        long long x = target;
        long long steps = 0;

        while (x > startValue) {
            if (x & 1LL) {
                ++x;
            } else {
                x /= 2;
            }
            ++steps;
        }

        steps += startValue - x;
        return (int)steps;
    }
};

/*
DRY RUN
startValue = 3, target = 10

Work backward:
10 is even -> 10 / 2 = 5       (1 operation)
5 is odd  -> 5 + 1 = 6         (2 operations)
6 is even -> 6 / 2 = 3         (3 operations)

Reached startValue. Answer = 3.

Another example:
startValue = 5, target = 8
8 -> 4 (halve)
4 <= 5, so add 5 - 4 = 1 reverse increment.
Total = 1 + 1 = 2 operations.

COMPLEXITY SUMMARY
1. Forward BFS                    O(V + E) explored    O(V)
2. Forward Dijkstra               O((V+E) log V)       O(V)
3. Forward DFS                    Exponential          O(depth)
4. Bounded relaxation/BFS         O(V + E)             O(target)
5. Reverse BFS                    O(V + E) explored    O(V)
6. Reverse recursive greedy       O(log target)        O(log target)
7. Reverse iterative greedy       O(log target)        O(1)
8. Reverse greedy early case      O(log target)        O(1)
9. Reverse greedy with long long  O(log target)        O(1)

V and E refer to the number of explored states and transitions in the bounded
state graph. The graph bound is only for educational search approaches.

BEST CHOICE
Use #7 or #8. The reverse greedy solution handles target up to 10^9
efficiently. BFS, DFS, and Dijkstra are not suitable for the maximum range.
*/
