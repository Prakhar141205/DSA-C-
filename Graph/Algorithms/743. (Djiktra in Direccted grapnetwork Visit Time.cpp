/*
LeetCode 743: Network Delay Time
Copy one Solution class at a time and rename it to Solution.
Nodes are 1..n; edges are directed and have positive weights.
*/

#include <bits/stdc++.h>
using namespace std;

/*
1. Brute-force DFS over simple paths.
Exponential worst-case time; O(n) recursion/visited space.
Educational only. Positive weights mean an optimal path never needs a cycle.
*/
class Solution1 {
    vector<vector<pair<int,int>>> adj;
    vector<int> best;
    void dfs(int u, int cost, vector<char>& path) {
        if (cost >= best[u]) return;
        best[u] = cost;
        path[u] = true;
        for (auto [v,w] : adj[u])
            if (!path[v]) dfs(v, cost + w, path);
        path[u] = false;
    }
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        adj.assign(n+1, {});
        for (auto& e : times) adj[e[0]].push_back({e[1],e[2]});
        best.assign(n+1, INT_MAX);
        vector<char> path(n+1, false);
        dfs(k, 0, path);
        int ans = 0;
        for (int i=1; i<=n; ++i) {
            if (best[i] == INT_MAX) return -1;
            ans = max(ans, best[i]);
        }
        return ans;
    }
};

/*
2. Bellman-Ford.
Relax all edges n-1 times, with early stopping.
Time O(n*m), auxiliary space O(n). Correct but slower than Dijkstra here.
*/
class Solution2 {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        const long long INF = (1LL<<60);
        vector<long long> dist(n+1, INF);
        dist[k] = 0;
        for (int pass=1; pass<n; ++pass) {
            bool changed = false;
            for (auto& e : times) {
                int u=e[0], v=e[1], w=e[2];
                if (dist[u] != INF && dist[u]+w < dist[v]) {
                    dist[v] = dist[u]+w;
                    changed = true;
                }
            }
            if (!changed) break;
        }
        long long ans = 0;
        for (int i=1; i<=n; ++i) {
            if (dist[i] == INF) return -1;
            ans = max(ans, dist[i]);
        }
        return (int)ans;
    }
};

/*
3. Dijkstra with set (decrease-key).
Erase the old {distance,node} before inserting its improved distance.
Time O((n+m) log n), space O(n+m) including adjacency.
*/
class Solution3 {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int,int>>> adj(n+1);
        for (auto& e : times) adj[e[0]].push_back({e[1],e[2]});

        vector<int> dist(n+1, INT_MAX);
        set<pair<int,int>> st;
        dist[k]=0;
        st.insert({0,k});

        while (!st.empty()) {
            auto [d,u] = *st.begin();
            st.erase(st.begin());

            for (auto [v,w] : adj[u]) {
                long long nd = 1LL*d+w;
                if (nd < dist[v]) {
                    if (dist[v] != INT_MAX) st.erase({dist[v],v});
                    dist[v] = (int)nd;
                    st.insert({dist[v],v});
                }
            }
        }

        int ans=0;
        for (int i=1; i<=n; ++i) {
            if (dist[i] == INT_MAX) return -1;
            ans=max(ans,dist[i]);
        }
        return ans;
    }
};

/*
4. Dijkstra with min-priority_queue (recommended).
The heap can contain duplicate entries. Skip stale entries on pop.
Time O((n+m) log n) for the usual simple-graph bound.
Space O(n+m), including adjacency and heap.
*/
class Solution4 {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int,int>>> adj(n+1);
        for (auto& e : times) adj[e[0]].push_back({e[1],e[2]});

        vector<int> dist(n+1, INT_MAX);
        priority_queue<pair<int,int>,
                       vector<pair<int,int>>,
                       greater<pair<int,int>>> pq;

        dist[k]=0;
        pq.push({0,k});

        while (!pq.empty()) {
            auto [d,u]=pq.top();
            pq.pop();

            if (d != dist[u]) continue; // stale entry

            for (auto [v,w] : adj[u]) {
                long long nd=1LL*d+w;
                if (nd < dist[v]) {
                    dist[v]=(int)nd;
                    pq.push({dist[v],v});
                }
            }
        }

        int ans=0;
        for (int i=1; i<=n; ++i) {
            if (dist[i] == INT_MAX) return -1;
            ans=max(ans,dist[i]);
        }
        return ans;
    }
};

/*
Why Network Delay Time is the MAXIMUM shortest distance:
The signal reaches each node at its shortest-path distance from k.
The last node to receive it is the node with the largest such distance.
If any node has distance INT_MAX, it is unreachable, so return -1.

Your set implementation is logically correct. Improvements:
- Use vector<vector<pair<int,int>>> instead of unordered_map: nodes are 1..n.
- Use 1LL*d + wt for safe intermediate addition.
- You can return -1 as soon as an unreachable node is found.
- Your set erase is the decrease-key pattern; no stale-entry check is needed
  because the old pair is explicitly erased.

Example:
times = [[2,1,1],[2,3,1],[3,4,1]], n=4, k=2
shortest distances: [1,0,1,2], so answer = 2.
*/
