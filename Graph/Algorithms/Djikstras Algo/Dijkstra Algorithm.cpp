/*
Dijkstra's Algorithm (GFG-style adjacency list)
Input:
  adj[u] contains entries {v, weight} for directed edge u -> v.
For an undirected graph, GFG generally stores both directions in adj.

Copy one Solution class at a time. The expected GFG signature is:
vector<int> dijkstra(vector<vector<vector<int>>>& adj, int src)
*/

#include <bits/stdc++.h>
using namespace std;

/*
Approach 1: Bellman-Ford (baseline / slower alternative).
Relax every edge V-1 times. This is not Dijkstra, but is a useful
comparison and works even with negative edge weights (without reachable
negative cycles).

Time: O(V*E)
Space: O(V)

The problem's non-negative weights make Dijkstra preferable.
*/
class Solution1 {
public:
    vector<int> dijkstra(vector<vector<vector<int>>>& adj, int src) {
        int n = adj.size();
        const long long INF = (1LL << 60);
        vector<long long> dist(n, INF);
        dist[src] = 0;

        for (int pass = 1; pass < n; ++pass) {
            bool changed = false;

            for (int u = 0; u < n; ++u) {
                if (dist[u] == INF) continue;

                for (const auto& edge : adj[u]) {
                    int v = edge[0];
                    int wt = edge[1];

                    if (dist[u] + wt < dist[v]) {
                        dist[v] = dist[u] + wt;
                        changed = true;
                    }
                }
            }

            if (!changed) break;
        }

        vector<int> ans(n);
        for (int i = 0; i < n; ++i)
            ans[i] = (dist[i] == INF ? INT_MAX : static_cast<int>(dist[i]));
        return ans;
    }
};

/*
Approach 2: Dijkstra with a set (decrease-key behavior).
The set stores exactly one current {distance,node} pair per reachable node.
When a shorter distance is found, erase the old pair before inserting the new one.

Time: O((V+E) log V)
Space: O(V), excluding input adjacency list.
*/
class Solution2 {
public:
    vector<int> dijkstra(vector<vector<vector<int>>>& adj, int src) {
        int n = adj.size();
        const int INF = INT_MAX;
        vector<int> dist(n, INF);
        set<pair<int, int>> st;

        dist[src] = 0;
        st.insert({0, src});

        while (!st.empty()) {
            auto [d, u] = *st.begin();
            st.erase(st.begin());

            for (const auto& edge : adj[u]) {
                int v = edge[0];
                int wt = edge[1];

                // Use long long for the addition to avoid intermediate overflow.
                long long candidate = 1LL * d + wt;
                if (candidate < dist[v]) {
                    if (dist[v] != INF)
                        st.erase({dist[v], v});

                    dist[v] = static_cast<int>(candidate);
                    st.insert({dist[v], v});
                }
            }
        }

        return dist;
    }
};

/*
Approach 3: Dijkstra with min-priority_queue (standard / recommended).
A priority_queue does not support decrease-key. Therefore, when a better
distance is found, push a new pair. Older pairs remain in the heap.

CRITICAL: discard a popped pair if its distance is no longer dist[u].
This stale-entry check avoids rescanning adjacency lists for obsolete entries.

Time: O((V+E) log E), commonly stated as O((V+E) log V) for simple graphs.
Space: O(V+E) worst case for heap and distance storage.
*/
class Solution3 {
public:
    vector<int> dijkstra(vector<vector<vector<int>>>& adj, int src) {
        int n = adj.size();
        const int INF = INT_MAX;
        vector<int> dist(n, INF);

        // {distance, node}; greater<> makes this a min-heap.
        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            // Skip outdated heap entries.
            if (d != dist[u]) continue;

            for (const auto& edge : adj[u]) {
                int v = edge[0];
                int wt = edge[1];

                long long candidate = 1LL * d + wt;
                if (candidate < dist[v]) {
                    dist[v] = static_cast<int>(candidate);
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
    }
};

/*
Approach 4: Dijkstra with a min-heap and long long distances internally.
Use this if path sums might exceed int range. The GFG signature still returns
vector<int>, so this version assumes every finite answer fits in int; otherwise
the platform's required return type itself cannot represent the answer.

Algorithmic complexity is the same as Approach 3.
*/
class Solution4 {
public:
    vector<int> dijkstra(vector<vector<vector<int>>>& adj, int src) {
        int n = adj.size();
        const long long INF = (1LL << 60);
        vector<long long> dist(n, INF);

        using State = pair<long long, int>;
        priority_queue<State, vector<State>, greater<State>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d != dist[u]) continue;

            for (const auto& edge : adj[u]) {
                int v = edge[0];
                int wt = edge[1];
                long long nd = d + wt;

                if (nd < dist[v]) {
                    dist[v] = nd;
                    pq.push({nd, v});
                }
            }
        }

        vector<int> ans(n);
        for (int i = 0; i < n; ++i)
            ans[i] = (dist[i] == INF ? INT_MAX : static_cast<int>(dist[i]));
        return ans;
    }
};

/*
Why the original implementation can get TLE:

1. Missing stale-entry check:
   You pop {cost,node}, but never test cost == ans[node].
   Suppose node x is first reached with cost 100, then later improved to 5.
   Both {100,x} and {5,x} are in the heap. When {100,x} is eventually popped,
   your code scans all outgoing edges of x again using the obsolete cost.
   This can cause a large amount of redundant work. Add:
       if (cost != ans[node]) continue;

2. Unnecessary graph copy:
   The input is already an adjacency list. Building an unordered_map<int,
   vector<pair<int,int>>> duplicates the graph and adds hashing/allocation
   overhead. Iterate adj[node] directly.

3. Unnecessary unordered_map:
   Nodes are numbered 0..n-1, so vector-based adjacency is more efficient
   than a hash map. In this case, no separate graph is needed at all.

4. Use a const reference when scanning edges:
       for (const auto& edge : adj[node])
   This avoids copying each inner vector.

5. Dijkstra requires non-negative edge weights.
   If negative weights exist, this algorithm is not valid.

The main TLE fix is the stale-entry check. The graph-copy removal also improves
runtime and memory use.
*/
