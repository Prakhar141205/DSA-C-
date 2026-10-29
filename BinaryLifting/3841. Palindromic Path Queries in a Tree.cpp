/*
LeetCode 3841: Palindromic Path Queries in a Tree
Approaches from brute force to optimal.

Function signature:
vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                            string s, vector<string>& queries)

A path's letters can be rearranged into a palindrome iff at most one
character occurs an odd number of times.

Represent the parity of all 26 character counts as a bitmask:
bit 0 = 'a', bit 1 = 'b', ..., bit 25 = 'z'.
A mask is valid for a palindrome permutation iff popcount(mask) <= 1.

This file contains multiple alternative Solution classes. Copy ONE class
and rename it to Solution before submitting.
*/

#include <bits/stdc++.h>
using namespace std;

/*
APPROACH 1: Brute force — find every path and count its characters
- For every query, BFS/DFS from u to v to recover the path.
- Count characters on that path.
- For updates, just change s[u].

Time: O(n + q*n) in the worst case (path search and scan per query).
Space: O(n) per query for traversal/parent information.
This is simple but too slow for n,q up to 50,000.
*/
class Solution1 {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<bool> ans;
        for (const string& query : queries) {
            stringstream ss(query);
            string type;
            int u;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;
                s[u] = c;
                continue;
            }

            int v;
            ss >> v;
            vector<int> parent(n, -1);
            queue<int> qu;
            qu.push(u);
            parent[u] = u;

            while (!qu.empty() && parent[v] == -1) {
                int x = qu.front();
                qu.pop();
                for (int y : adj[x]) {
                    if (parent[y] == -1) {
                        parent[y] = x;
                        qu.push(y);
                    }
                }
            }

            int mask = 0;
            int x = v;
            while (x != u) {
                mask ^= (1 << (s[x] - 'a'));
                x = parent[x];
            }
            mask ^= (1 << (s[u] - 'a'));

            ans.push_back(__builtin_popcount((unsigned)mask) <= 1);
        }

        return ans;
    }
};

/*
APPROACH 2: Root the tree + binary lifting LCA + character frequency masks
- Root the tree at 0 and preprocess parent/depth/binary-lifting ancestors.
- For a path query, climb from u and v to their LCA and XOR each node's
  character bit. Updates are handled by reading the current s[node] value.
- This is an improvement over brute force for shallow paths but still can
  be O(n) per query if masks are not supported by a dynamic range structure.
This class intentionally demonstrates the LCA path-walk method.

Time: O(n log n + q*n) worst case.
Space: O(n log n).
*/
class Solution2 {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n) ++LOG;
        vector<vector<int>> up(LOG, vector<int>(n, 0));
        vector<int> depth(n, 0), parent(n, 0), order;
        order.reserve(n);

        vector<int> st = {0};
        parent[0] = 0;
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            order.push_back(u);
            for (int v : adj[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                st.push_back(v);
            }
        }

        for (int u = 0; u < n; ++u) up[0][u] = parent[u];
        for (int k = 1; k < LOG; ++k)
            for (int u = 0; u < n; ++u)
                up[k][u] = up[k - 1][up[k - 1][u]];

        auto lca = [&](int a, int b) {
            if (depth[a] < depth[b]) swap(a, b);
            int diff = depth[a] - depth[b];
            for (int k = 0; k < LOG; ++k)
                if (diff & (1 << k)) a = up[k][a];
            if (a == b) return a;
            for (int k = LOG - 1; k >= 0; --k) {
                if (up[k][a] != up[k][b]) {
                    a = up[k][a];
                    b = up[k][b];
                }
            }
            return parent[a];
        };

        vector<bool> ans;
        for (const string& query : queries) {
            stringstream ss(query);
            string type;
            int u;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;
                s[u] = c;
                continue;
            }

            int v;
            ss >> v;
            int w = lca(u, v);
            int mask = 0;

            int x = u;
            while (x != w) {
                mask ^= (1 << (s[x] - 'a'));
                x = parent[x];
            }
            x = v;
            while (x != w) {
                mask ^= (1 << (s[x] - 'a'));
                x = parent[x];
            }
            mask ^= (1 << (s[w] - 'a'));

            ans.push_back(__builtin_popcount((unsigned)mask) <= 1);
        }

        return ans;
    }
};

/*
APPROACH 3: Euler tour + subtree XOR + Fenwick tree (OPTIMAL)
Key observation:
- Give each node tin[u] using a DFS preorder.
- Store one bit for its current character at tin[u].
- Updating a node toggles the old-character bit and the new-character bit
  at that Euler position. A Fenwick tree stores XOR masks over Euler order.
- XOR of root-to-node masks can be obtained as the XOR over the Euler
  preorder prefix [0, tin[u]] ONLY if each node's own character is stored
  at its entry and the Fenwick prefix is not being interpreted as a path.
  Therefore, this is not a valid root-path solution by itself.
Use HLD below for a valid dynamic path XOR solution.
*/

/*
APPROACH 3: Heavy-Light Decomposition (HLD) + segment tree of XOR masks
- Decompose every root-to-node path into O(log n) contiguous ranges.
- Flatten nodes by HLD position.
- Each segment-tree leaf stores 1 << (s[u]-'a'); each internal node is XOR.
- Point update changes one leaf.
- Path query XORs the ranges on u-v path.
- At most one bit set => can rearrange path into a palindrome.

Time: O(log^2 n) per path query, O(log n) per update.
Space: O(n).
This approach is robust and meets constraints.
*/
class Solution3 {
    struct SegTree {
        int size;
        vector<int> tree;

        explicit SegTree(int n) {
            size = 1;
            while (size < n) size <<= 1;
            tree.assign(2 * size, 0);
        }

        void build(const vector<int>& a) {
            for (int i = 0; i < (int)a.size(); ++i)
                tree[size + i] = a[i];
            for (int i = size - 1; i > 0; --i)
                tree[i] = tree[i << 1] ^ tree[i << 1 | 1];
        }

        void update(int pos, int value) {
            int p = size + pos;
            tree[p] = value;
            while (p > 1) {
                p >>= 1;
                tree[p] = tree[p << 1] ^ tree[p << 1 | 1];
            }
        }

        int query(int left, int right) { // inclusive
            int result = 0;
            int l = left + size;
            int r = right + size;
            while (l <= r) {
                if (l & 1) result ^= tree[l++];
                if (!(r & 1)) result ^= tree[r--];
                l >>= 1;
                r >>= 1;
            }
            return result;
        }
    };

    vector<vector<int>> adj;
    vector<int> parent, depth, subtreeSize, heavy, head, pos;
    int timer = 0;
    unique_ptr<SegTree> seg;

    int dfsSize(int u, int p) {
        parent[u] = p;
        subtreeSize[u] = 1;
        int largest = 0;
        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            int childSize = dfsSize(v, u);
            subtreeSize[u] += childSize;
            if (childSize > largest) {
                largest = childSize;
                heavy[u] = v;
            }
        }
        return subtreeSize[u];
    }

    void decompose(int u, int h, const string& s, vector<int>& base) {
        head[u] = h;
        pos[u] = timer;
        base[timer++] = 1 << (s[u] - 'a');

        if (heavy[u] != -1)
            decompose(heavy[u], h, s, base);

        for (int v : adj[u]) {
            if (v == parent[u] || v == heavy[u]) continue;
            decompose(v, v, s, base);
        }
    }

    int pathMask(int u, int v) {
        int mask = 0;

        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            mask ^= seg->query(pos[head[u]], pos[u]);
            u = parent[head[u]];
        }

        if (depth[u] > depth[v]) swap(u, v);
        mask ^= seg->query(pos[u], pos[v]);
        return mask;
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        adj.assign(n, {});
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        parent.assign(n, 0);
        depth.assign(n, 0);
        subtreeSize.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        pos.assign(n, 0);
        timer = 0;

        dfsSize(0, 0);

        vector<int> base(n);
        decompose(0, 0, s, base);

        seg = make_unique<SegTree>(n);
        seg->build(base);

        vector<bool> ans;
        for (const string& query : queries) {
            stringstream ss(query);
            string type;
            int u;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;
                s[u] = c;
                seg->update(pos[u], 1 << (c - 'a'));
            } else {
                int v;
                ss >> v;
                int mask = pathMask(u, v);
                ans.push_back(__builtin_popcount((unsigned)mask) <= 1);
            }
        }
        return ans;
    }
};

/*
APPROACH 4: Euler tour + root-path prefix masks + Fenwick tree + LCA
Another valid O(log n) path-query approach:
- Root-to-node parity masks P[u] are XORs of character bits along root->u.
- Changing node u from old to new toggles delta = bit(old) XOR bit(new)
  for every descendant's root-path mask. This is a subtree range-XOR update
  in Euler-tour order, supported by a Fenwick tree used as a difference array.
- Query path mask = P[u] XOR P[v] XOR bit(character[LCA(u,v)]).
This is asymptotically faster than HLD's O(log^2 n) path queries, but has
more intricate range-XOR / LCA bookkeeping. HLD above is included as the
recommended straightforward optimal implementation.
*/
class Solution4 {
    int n, LOG;
    vector<vector<int>> adj, up;
    vector<int> tin, tout, depth;
    vector<int> bit; // XOR Fenwick tree (difference array for range XOR updates)
    int timer = 0;

    void fenwickXorUpdate(int i, int value) {
        for (++i; i <= n; i += i & -i) bit[i] ^= value;
    }

    int fenwickPrefix(int i) const {
        int result = 0;
        for (++i; i > 0; i -= i & -i) result ^= bit[i];
        return result;
    }

    void rangeXor(int l, int r, int value) {
        fenwickXorUpdate(l, value);
        if (r + 1 < n) fenwickXorUpdate(r + 1, value);
    }

    void dfs(int u, int p, const string& s) {
        tin[u] = timer++;
        up[0][u] = p;
        for (int k = 1; k < LOG; ++k)
            up[k][u] = up[k - 1][up[k - 1][u]];

        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u, s);
        }
        tout[u] = timer - 1;
    }

    int lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        int diff = depth[a] - depth[b];
        for (int k = 0; k < LOG; ++k)
            if (diff & (1 << k)) a = up[k][a];

        if (a == b) return a;

        for (int k = LOG - 1; k >= 0; --k) {
            if (up[k][a] != up[k][b]) {
                a = up[k][a];
                b = up[k][b];
            }
        }
        return up[0][a];
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        this->n = n;
        adj.assign(n, {});
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        LOG = 1;
        while ((1 << LOG) <= n) ++LOG;
        up.assign(LOG, vector<int>(n, 0));
        tin.assign(n, 0);
        tout.assign(n, 0);
        depth.assign(n, 0);
        bit.assign(n + 1, 0);
        timer = 0;

        dfs(0, 0, s);

        // P[u] = parity mask on root -> u path.
        vector<int> rootMask(n, 0);
        vector<int> nodes(n);
        iota(nodes.begin(), nodes.end(), 0);
        sort(nodes.begin(), nodes.end(), [&](int a, int b) {
            return depth[a] < depth[b];
        });
        for (int u : nodes) {
            int p = up[0][u];
            rootMask[u] = (u == 0 ? 0 : rootMask[p]) ^ (1 << (s[u] - 'a'));
        }

        vector<bool> ans;
        for (const string& query : queries) {
            stringstream ss(query);
            string type;
            int u;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;
                int oldBit = 1 << (s[u] - 'a');
                int newBit = 1 << (c - 'a');
                int delta = oldBit ^ newBit;
                s[u] = c;
                rangeXor(tin[u], tout[u], delta);
            } else {
                int v;
                ss >> v;
                int w = lca(u, v);
                int pu = rootMask[u] ^ fenwickPrefix(tin[u]);
                int pv = rootMask[v] ^ fenwickPrefix(tin[v]);
                int mask = pu ^ pv ^ (1 << (s[w] - 'a'));
                ans.push_back(__builtin_popcount((unsigned)mask) <= 1);
            }
        }
        return ans;
    }
};

/*
COMPLEXITY SUMMARY:
1. Brute force path recovery + counting:       O(n) per query, O(n) space.
2. LCA + explicit path walk:                   O(n) per query, O(n log n) space.
3. HLD + segment tree (robust solution):       O(log^2 n) query, O(log n) update, O(n) space.
4. Euler + subtree range XOR + LCA:             O(log n) query/update, O(n log n) space.

Practical recommendation: use Approach 3 (HLD + segment tree) if you want a
clear, self-contained, dynamic path-XOR implementation. The recursion in the
HLD DFS can reach depth n on a chain; if stack limits are strict, convert the
DFS traversals to iterative versions.
*/
