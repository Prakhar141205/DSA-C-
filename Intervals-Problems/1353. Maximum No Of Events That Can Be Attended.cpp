#include <bits/stdc++.h>
using namespace std;

/*
LeetCode 1353 — Maximum Number of Events That Can Be Attended

This file keeps multiple approaches in one place.
LeetCode's required method is:
    int maxEvents(vector<vector<int>>& events)

The default maxEvents() below uses the optimal min-heap sweep-line approach.

Approaches included:
1. Brute-force backtracking — exponential; useful only for tiny inputs.
2. Day-by-day min-heap — O((D + n) log n), where D is the maximum end day.
3. Sort by start + min-heap — same optimal greedy idea, O(n log n + D log n).
4. Sort by end + Disjoint Set Union (DSU) — near O(n log n + D alpha(D)).
5. Sort by end + segment tree — O(n log n + n log D).
6. Sort by end + linear scan for a free day — simple but can be O(nD).

Important greedy idea:
Always attend the available event that ends earliest. This preserves later days
for events with later deadlines.
*/

class Solution {
private:
    // -----------------------------------------------------------------
    // Approach 1: Brute force / backtracking (exponential)
    // Only practical for very small inputs.
    // -----------------------------------------------------------------
    int bruteDfs(const vector<vector<int>>& events, vector<bool>& used, int day) {
        int n = (int)events.size();
        int maxEnd = 0;
        for (const auto& e : events) maxEnd = max(maxEnd, e[1]);
        if (day > maxEnd) return 0;

        int best = 0;

        for (int i = 0; i < n; ++i) {
            if (used[i]) continue;

            int start = events[i][0];
            int end = events[i][1];

            if (start <= day && day <= end) {
                used[i] = true;
                best = max(best, 1 + bruteDfs(events, used, day + 1));
                used[i] = false;
            }
        }

        // Skip this day.
        best = max(best, bruteDfs(events, used, day + 1));
        return best;
    }

    // -----------------------------------------------------------------
    // Approach 4: DSU successor structure.
    // find(day) returns the earliest unoccupied day >= day.
    // -----------------------------------------------------------------
    struct DSU {
        vector<int> parent;

        explicit DSU(int n) : parent(n + 1) {
            iota(parent.begin(), parent.end(), 0);
        }

        int find(int x) {
            if (parent[x] == x) return x;
            return parent[x] = find(parent[x]);
        }

        // Mark day x as occupied; the next free day becomes find(x + 1).
        void occupy(int x) {
            parent[x] = find(x + 1);
        }
    };

    // -----------------------------------------------------------------
    // Approach 5: Segment tree storing the number of free days.
    // Find the earliest free day in [ql, qr].
    // -----------------------------------------------------------------
    struct SegmentTree {
        int n;
        vector<int> tree;

        explicit SegmentTree(int size) : n(size), tree(4 * size + 4, 0) {
            build(1, 1, n);
        }

        void build(int node, int left, int right) {
            if (left == right) {
                tree[node] = 1; // This day is initially free.
                return;
            }
            int mid = left + (right - left) / 2;
            build(node * 2, left, mid);
            build(node * 2 + 1, mid + 1, right);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }

        void occupy(int node, int left, int right, int pos) {
            if (left == right) {
                tree[node] = 0;
                return;
            }
            int mid = left + (right - left) / 2;
            if (pos <= mid) occupy(node * 2, left, mid, pos);
            else occupy(node * 2 + 1, mid + 1, right, pos);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }

        int firstFree(int node, int left, int right, int ql, int qr) {
            if (right < ql || left > qr || tree[node] == 0) return -1;
            if (left == right) return left;

            int mid = left + (right - left) / 2;
            int answer = firstFree(node * 2, left, mid, ql, qr);
            if (answer != -1) return answer;
            return firstFree(node * 2 + 1, mid + 1, right, ql, qr);
        }

        void occupy(int pos) {
            occupy(1, 1, n, pos);
        }

        int firstFree(int left, int right) {
            if (left > right) return -1;
            return firstFree(1, 1, n, left, right);
        }
    };

public:
    // Default LeetCode solution: sort by start day + min-heap of end days.
    // Time: O(n log n + D log n), Space: O(n).
    int maxEvents(vector<vector<int>>& events) {
        return maxEventsMinHeap(events);
    }

    // -----------------------------------------------------------------
    // Approach 1: Brute force / backtracking.
    // WARNING: Exponential and not suitable for the given constraints.
    // -----------------------------------------------------------------
    int maxEventsBruteForce(vector<vector<int>>& events) {
        if (events.empty()) return 0;

        int maxEnd = 0;
        for (const auto& e : events) maxEnd = max(maxEnd, e[1]);

        vector<bool> used(events.size(), false);
        return bruteDfs(events, used, 1);
    }

    // -----------------------------------------------------------------
    // Approach 2: Sweep days + min-heap.
    // On each day, add events that have started, remove expired events,
    // then attend the available event with the earliest ending day.
    // Time: O((D + n) log n), Space: O(n).
    // -----------------------------------------------------------------
    int maxEventsMinHeap(vector<vector<int>>& events) {
        sort(events.begin(), events.end());

        priority_queue<int, vector<int>, greater<int>> minEnd;
        int n = (int)events.size();
        int i = 0;
        int day = 1;
        int attended = 0;

        while (i < n || !minEnd.empty()) {
            if (minEnd.empty() && i < n && day < events[i][0]) {
                day = events[i][0];
            }

            while (i < n && events[i][0] <= day) {
                minEnd.push(events[i][1]);
                ++i;
            }

            while (!minEnd.empty() && minEnd.top() < day) {
                minEnd.pop();
            }

            if (!minEnd.empty()) {
                minEnd.pop(); // Attend the event ending earliest.
                ++attended;
                ++day;
            }
        }

        return attended;
    }

    // -----------------------------------------------------------------
    // Approach 3: Explicit start-day sorting + min-heap.
    // Same greedy algorithm as Approach 2, written separately so it can
    // be studied as a standalone implementation.
    // Time: O(n log n + D log n), Space: O(n).
    // -----------------------------------------------------------------
    int maxEventsSortStartHeap(vector<vector<int>>& events) {
        vector<vector<int>> sortedEvents = events;
        sort(sortedEvents.begin(), sortedEvents.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[0] < b[0];
             });

        priority_queue<int, vector<int>, greater<int>> ends;
        int i = 0, day = 1, answer = 0;
        int n = (int)sortedEvents.size();

        while (i < n || !ends.empty()) {
            if (ends.empty() && i < n && day < sortedEvents[i][0]) {
                day = sortedEvents[i][0];
            }

            while (i < n && sortedEvents[i][0] <= day) {
                ends.push(sortedEvents[i][1]);
                ++i;
            }

            while (!ends.empty() && ends.top() < day) ends.pop();

            if (!ends.empty()) {
                ends.pop();
                ++answer;
                ++day;
            }
        }

        return answer;
    }

    // -----------------------------------------------------------------
    // Approach 4: Sort by ending day + DSU.
    // For each event in increasing end-day order, assign its earliest
    // free day >= start. If that day is <= end, attend the event.
    // Time: O(n log n + D alpha(D)), Space: O(D).
    // -----------------------------------------------------------------
    int maxEventsDSU(vector<vector<int>>& events) {
        vector<vector<int>> sortedEvents = events;
        sort(sortedEvents.begin(), sortedEvents.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 if (a[1] != b[1]) return a[1] < b[1];
                 return a[0] < b[0];
             });

        int maxDay = 0;
        for (const auto& e : sortedEvents) maxDay = max(maxDay, e[1]);

        DSU dsu(maxDay + 1);
        int answer = 0;

        for (const auto& e : sortedEvents) {
            int day = dsu.find(e[0]);
            if (day <= e[1]) {
                ++answer;
                dsu.occupy(day);
            }
        }

        return answer;
    }

    // -----------------------------------------------------------------
    // Approach 5: Sort by ending day + segment tree.
    // Find the first free day inside each event's interval.
    // Time: O(n log n + n log D), Space: O(D).
    // -----------------------------------------------------------------
    int maxEventsSegmentTree(vector<vector<int>>& events) {
        vector<vector<int>> sortedEvents = events;
        sort(sortedEvents.begin(), sortedEvents.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 if (a[1] != b[1]) return a[1] < b[1];
                 return a[0] < b[0];
             });

        int maxDay = 0;
        for (const auto& e : sortedEvents) maxDay = max(maxDay, e[1]);

        SegmentTree seg(maxDay);
        int answer = 0;

        for (const auto& e : sortedEvents) {
            int day = seg.firstFree(e[0], e[1]);
            if (day != -1) {
                ++answer;
                seg.occupy(day);
            }
        }

        return answer;
    }

    // -----------------------------------------------------------------
    // Approach 6: Sort by end day + linear scan for a free day.
    // Easy to understand, but can take O(nD) time.
    // -----------------------------------------------------------------
    int maxEventsLinearScan(vector<vector<int>>& events) {
        vector<vector<int>> sortedEvents = events;
        sort(sortedEvents.begin(), sortedEvents.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 if (a[1] != b[1]) return a[1] < b[1];
                 return a[0] < b[0];
             });

        int maxDay = 0;
        for (const auto& e : sortedEvents) maxDay = max(maxDay, e[1]);

        vector<bool> occupied(maxDay + 2, false);
        int answer = 0;

        for (const auto& e : sortedEvents) {
            for (int day = e[0]; day <= e[1]; ++day) {
                if (!occupied[day]) {
                    occupied[day] = true;
                    ++answer;
                    break;
                }
            }
        }

        return answer;
    }
};

/*
Expected results:
events = {{1,2},{2,3},{3,4}}          -> 3
events = {{1,2},{2,3},{3,4},{1,2}}    -> 4

Recommended approach to submit:
    Solution::maxEvents()  // min-heap greedy, O(n log n + D log n)

For LeetCode, copy the class Solution only. The extra methods are optional
study implementations; you only need maxEvents() for submission.
*/




