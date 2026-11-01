/*
LeetCode 991 — Broken Calculator
Original source: Greedy Algorithm/brokenCalcualtor.cpp
Original source files: 1
Approaches implemented: 2
Recommended: SolutionReverseGreedy

Approach index:
1. Forward BFS over a bounded state graph (small values only)
2. Reverse greedy from target (recommended)
*/

#include <algorithm>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

// 1. Forward BFS.
// Edges are x -> 2*x and x -> x-1, each with unit cost.
// Time/space: O(target) states in this educational bounded implementation.
// The state cap and explicit target cap make it unsuitable for large inputs.
class SolutionForwardBFS {
public:
    int brokenCalc(int startValue, int target) {
        if (startValue >= target) return startValue - target;
        if (target > 200000) return -1;

        const int upperBound = 2 * target;
        vector<int> distance(upperBound + 1, -1);
        queue<int> q;
        distance[startValue] = 0;
        q.push(startValue);

        while (!q.empty()) {
            const int current = q.front();
            q.pop();
            if (current == target) return distance[current];

            const long long doubled = 2LL * current;
            if (doubled <= upperBound &&
                distance[(int)doubled] == -1) {
                distance[(int)doubled] = distance[current] + 1;
                q.push((int)doubled);
            }
            if (current > 1 && distance[current - 1] == -1) {
                distance[current - 1] = distance[current] + 1;
                q.push(current - 1);
            }
        }
        return -1;
    }
};

// 2. Reverse greedy.
// Reverse x-1 as x+1 when odd, and reverse doubling as x/2 when even.
// Time: O(log target); auxiliary space: O(1).
class SolutionReverseGreedy {
public:
    int brokenCalc(int startValue, int target) {
        long long current = target;
        int operations = 0;

        while (current > startValue) {
            if (current & 1LL) {
                ++current;
            } else {
                current /= 2;
            }
            ++operations;
        }
        return operations + startValue - (int)current;
    }
};
