/*
LeetCode 3970. Shortest Path With At Most K Consecutive Identical Characters
Approaches: brute-force DFS, Bellman-Ford on states, and optimal Dijkstra.

State (u, run): currently at node u, and the consecutive run of labels[u]
along the path has length run. Starting state is (0, 1).

For edge u -> v:
  nextRun = (labels[u] == labels[v]) ? run + 1 : 1
  The move is allowed only when nextRun <= k.

Copy ONE class at a time and rename it to Solution before submitting.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (1LL << 60);

struct Edge {
    int to, weight;
};

/*
Approach 1: Brute-force DFS over expanded states.
Educational only; exponential worst case, not suitable for full constraints.
A state cannot repeat on the current path: all edge weights are positive,
so an optimal path never needs to revisit the same expanded state.
Time: exponential worst case. Space: O(n*k) plus recursion stack.
*/
class Solution1 {
    int n, k;
    string labels;
    vector<vector<Edge>> graph;
    vector<vector<char>> onPath;
    ll best;

    void dfs(int u, int run, ll cost) {
        if (cost >= best) return;
        if (u == n - 1) {
            best = cost;
            return;
        }

        onPath[u][run] = true;
        for (const Edge& e : graph[u]) {
            int nextRun = (labels[u] == labels[e.to]) ? run + 1 : 1;
            if (nextRun > k || onPath[e.to][nextRun]) continue;
            dfs(e.to, nextRun, cost + e.weight);
        }
        onPath[u][run] = false;
    }

public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        this->n = n;
        this->k = k;
        this->labels = labels;
        graph.assign(n, {});
        for (const auto& e : edges) graph[e[0]].push_back({e[1], e[2]});
        onPath.assign(n, vector<char>(k + 1, false));
        best = INF;
        dfs(0, 1, 0);
        return best == INF ? -1 : static_cast<int>(best);
    }
};

/*
Approach 2: Bellman-Ford over expanded states.
Correct but too slow for maximum constraints.
V' = n*k states; E' <= m*k transitions.
Time: O(V' * E') = O(n*m*k^2); Space: O(n*k).
Transitions are generated on the fly instead of stored.
*/
class Solution2 {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<ll>> dist(n, vector<ll>(k + 1, INF));
        dist[0][1] = 0;

        for (int pass = 1; pass <= n * k - 1; ++pass) {
            bool changed = false;
            for (const auto& e : edges) {
                int u = e[0], v = e[1], w = e[2];
                for (int run = 1; run <= k; ++run) {
                    if (dist[u][run] == INF) continue;
                    int nextRun = (labels[u] == labels[v]) ? run + 1 : 1;
                    if (nextRun > k) continue;
                    ll candidate = dist[u][run] + w;
                    if (candidate < dist[v][nextRun]) {
                        dist[v][nextRun] = candidate;
                        changed = true;
                    }
                }
            }
            if (!changed) break;
        }

        ll answer = *min_element(dist[n - 1].begin() + 1, dist[n - 1].end());
        return answer == INF ? -1 : static_cast<int>(answer);
    }
};

/*
Approach 3: Dijkstra on expanded states (recommended).
V' = n*k, E' <= m*k.
Time: O((n*k + m*k) log(n*k)).
Space: O(n*k + m), including graph and distance storage.
*/
class Solution3 {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<Edge>> graph(n);
        for (const auto& e : edges) graph[e[0]].push_back({e[1], e[2]});

        vector<vector<ll>> dist(n, vector<ll>(k + 1, INF));
        using State = tuple<ll, int, int>; // cost, node, run
        priority_queue<State, vector<State>, greater<State>> pq;
        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [cost, u, run] = pq.top();
            pq.pop();
            if (cost != dist[u][run]) continue;
            if (u == n - 1) return static_cast<int>(cost);

            for (const Edge& e : graph[u]) {
                int v = e.to;
                int nextRun = (labels[u] == labels[v]) ? run + 1 : 1;
                if (nextRun > k) continue;
                ll nextCost = cost + e.weight;
                if (nextCost < dist[v][nextRun]) {
                    dist[v][nextRun] = nextCost;
                    pq.push({nextCost, v, nextRun});
                }
            }
        }
        return -1;
    }
};

/*
Approach 4: Dijkstra with flattened distance array.
Same optimal algorithm and complexity as Approach 3; only the state storage
is different. State id = node*(k+1) + run.
*/
class Solution4 {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<Edge>> graph(n);
        for (const auto& e : edges) graph[e[0]].push_back({e[1], e[2]});

        int width = k + 1;
        auto id = [width](int node, int run) { return node * width + run; };
        vector<ll> dist(n * width, INF);

        using State = tuple<ll, int, int>;
        priority_queue<State, vector<State>, greater<State>> pq;
        dist[id(0, 1)] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [cost, u, run] = pq.top();
            pq.pop();
            if (cost != dist[id(u, run)]) continue;
            if (u == n - 1) return static_cast<int>(cost);

            for (const Edge& e : graph[u]) {
                int v = e.to;
                int nextRun = (labels[u] == labels[v]) ? run + 1 : 1;
                if (nextRun > k) continue;
                ll nextCost = cost + e.weight;
                int nextId = id(v, nextRun);
                if (nextCost < dist[nextId]) {
                    dist[nextId] = nextCost;
                    pq.push({nextCost, v, nextRun});
                }
            }
        }
        return -1;
    }
};

/*
Example 1: labels = "aab", k = 1
0 -> 1 -> 2 spells "aab", invalid because "aa" has length 2.
0 -> 2 spells "ab", valid and costs 3. Answer = 3.

Key points:
- Count label[0] in the initial run: initial state is (0, 1).
- The graph is directed.
- The rule limits consecutive equal labels, not total occurrences.
- n == 1 returns 0.
- Use long long for distance calculations.

Recommendation: Solution3 is the standard solution to submit.
*/
