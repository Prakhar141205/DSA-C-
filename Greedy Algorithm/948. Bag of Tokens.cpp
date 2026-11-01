/*
LeetCode 948 — Bag of Tokens
Comprehensive C++ solution variations

Problem:
- Start with `power` and score = 0.
- Face-up token x: if power >= x, power -= x and score += 1.
- Face-down token x: if score >= 1, power += x and score -= 1.
- Each token can be played at most once.
- Maximize the highest score reached.

KEY GREEDY INSIGHT
Sort tokens increasingly.
1. If the cheapest remaining token is affordable, play it face-up.
   This gains one score for the least possible power.
2. Otherwise, if score > 0, play the most expensive remaining token face-down.
   This gains the most possible power for the one score spent.
3. Otherwise stop.

Maintain the maximum score reached, because a face-down move can reduce
the current score after a higher score has already been achieved.

The standard greedy solution is O(n log n) due to sorting and O(1)
auxiliary space apart from sorting implementation details.

Included approaches:
1. Brute-force DFS / backtracking (exponential).
2. Memoized DFS with bitmask (exponential; suitable only for small n).
3. BFS over all reachable states with bitmask (exponential).
4. Sorting + two pointers (canonical optimal greedy).
5. Sorting + deque (same greedy, different data structure).
6. Min-heap + max-heap with lazy deletion (O(n log n)).
7. Multiset greedy (O(n log n)).
8. Greedy with sorted array and explicit best-score tracking (compact form).

For the original constraints n <= 1000, use approaches 4–8.
Approaches 1–3 are included for learning the state-space formulation.
*/

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------------------------------------
// 1. BRUTE FORCE DFS / BACKTRACKING
// Try every legal next move for every unplayed token.
// State: used-token mask, current power, current score.
// Time: O(2^n * n) states/transitions in the rough upper bound; in practice
//       can be even larger due to different power/score values per mask.
// Space: O(n) recursion depth.
// Only suitable for very small n.
// -----------------------------------------------------------------------------
class Solution1_BruteForceDFS {
    int n;
    int best;

    void dfs(const vector<int>& tokens, int mask, int power, int score) {
        best = max(best, score);

        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) continue;

            // Face-up
            if (power >= tokens[i]) {
                dfs(tokens, mask | (1 << i),
                    power - tokens[i], score + 1);
            }

            // Face-down
            if (score >= 1) {
                dfs(tokens, mask | (1 << i),
                    power + tokens[i], score - 1);
            }
        }
    }

public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        n = (int)tokens.size();
        best = 0;

        // Bitmask implementation requires n to be small (e.g. <= 20).
        if (n > 20) return -1; // Not intended for original constraints.

        dfs(tokens, 0, power, 0);
        return best;
    }
};

// -----------------------------------------------------------------------------
// 2. MEMOIZED DFS WITH BITMASK
// Memoize (mask, power, score) to avoid re-exploring identical states.
// A token mask alone is not enough: power and score depend on the order and
// orientations of earlier moves.
// Exponential state space; suitable only for small n.
// -----------------------------------------------------------------------------
class Solution2_MemoizedDFS {
    struct State {
        int mask, power, score;

        bool operator==(const State& other) const {
            return mask == other.mask &&
                   power == other.power &&
                   score == other.score;
        }
    };

    struct StateHash {
        size_t operator()(const State& s) const {
            size_t h1 = hash<int>{}(s.mask);
            size_t h2 = hash<int>{}(s.power);
            size_t h3 = hash<int>{}(s.score);
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };

    int n;
    unordered_map<State, int, StateHash> memo;

    int dfs(const vector<int>& tokens, int mask, int power, int score) {
        State state{mask, power, score};
        auto it = memo.find(state);
        if (it != memo.end()) return it->second;

        int best = score;

        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) continue;

            if (power >= tokens[i]) {
                best = max(best, dfs(tokens, mask | (1 << i),
                                     power - tokens[i], score + 1));
            }

            if (score >= 1) {
                best = max(best, dfs(tokens, mask | (1 << i),
                                     power + tokens[i], score - 1));
            }
        }

        return memo[state] = best;
    }

public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        n = (int)tokens.size();
        if (n > 20) return -1; // Bitmask is deliberately for small n.
        memo.clear();
        return dfs(tokens, 0, power, 0);
    }
};

// -----------------------------------------------------------------------------
// 3. BFS OVER REACHABLE STATES
// Explore all legal states level by level.
// State includes mask, power, score. The answer is the maximum score seen.
// Exponential; for small n only.
// -----------------------------------------------------------------------------
class Solution3_BFS {
    struct State {
        int mask, power, score;
    };

    struct Key {
        int mask, power, score;
        bool operator==(const Key& other) const {
            return mask == other.mask &&
                   power == other.power &&
                   score == other.score;
        }
    };

    struct KeyHash {
        size_t operator()(const Key& s) const {
            return hash<int>{}(s.mask) ^
                   (hash<int>{}(s.power) << 1) ^
                   (hash<int>{}(s.score) << 2);
        }
    };

public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        int n = (int)tokens.size();
        if (n > 20) return -1;

        queue<State> q;
        unordered_set<Key, KeyHash> visited;

        q.push({0, power, 0});
        visited.insert({0, power, 0});

        int answer = 0;

        while (!q.empty()) {
            State cur = q.front();
            q.pop();

            answer = max(answer, cur.score);

            for (int i = 0; i < n; ++i) {
                if (cur.mask & (1 << i)) continue;

                int nextMask = cur.mask | (1 << i);

                if (cur.power >= tokens[i]) {
                    Key next{nextMask, cur.power - tokens[i],
                             cur.score + 1};
                    if (visited.insert(next).second) {
                        q.push({next.mask, next.power, next.score});
                    }
                }

                if (cur.score >= 1) {
                    Key next{nextMask, cur.power + tokens[i],
                             cur.score - 1};
                    if (visited.insert(next).second) {
                        q.push({next.mask, next.power, next.score});
                    }
                }
            }
        }

        return answer;
    }
};

// -----------------------------------------------------------------------------
// 4. SORT + TWO POINTERS — CANONICAL OPTIMAL GREEDY
// Time: O(n log n), Space: O(1) auxiliary (ignoring sort's stack).
// -----------------------------------------------------------------------------
class Solution4_TwoPointers {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        sort(tokens.begin(), tokens.end());

        int left = 0;
        int right = (int)tokens.size() - 1;
        int score = 0;
        int bestScore = 0;

        while (left <= right) {
            if (power >= tokens[left]) {
                // Cheapest token: spend minimum power to gain one score.
                power -= tokens[left];
                ++left;
                ++score;
                bestScore = max(bestScore, score);
            } else if (score > 0) {
                // Cannot afford the cheapest. Sell the most expensive token
                // to gain the maximum possible power.
                power += tokens[right];
                --right;
                --score;
            } else {
                // No affordable face-up token and no score to sell.
                break;
            }
        }

        return bestScore;
    }
};

// -----------------------------------------------------------------------------
// 5. SORT + DEQUE
// Same greedy decisions as two pointers. A deque makes front/back operations
// explicit.
// Time: O(n log n), Space: O(n) for the deque copy.
// -----------------------------------------------------------------------------
class Solution5_Deque {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        sort(tokens.begin(), tokens.end());
        deque<int> dq(tokens.begin(), tokens.end());

        int score = 0;
        int bestScore = 0;

        while (!dq.empty()) {
            if (power >= dq.front()) {
                power -= dq.front();
                dq.pop_front();
                ++score;
                bestScore = max(bestScore, score);
            } else if (score > 0) {
                power += dq.back();
                dq.pop_back();
                --score;
            } else {
                break;
            }
        }

        return bestScore;
    }
};

// -----------------------------------------------------------------------------
// 6. MIN-HEAP + MAX-HEAP WITH LAZY DELETION
// Both heaps contain every token. `used[i]` marks consumed indices.
// Heap entries are (value, index).
// Time: O(n log n), Space: O(n).
// This is an alternative data-structure implementation of the same greedy.
// -----------------------------------------------------------------------------
class Solution6_TwoHeaps {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        int n = (int)tokens.size();

        using P = pair<int, int>;
        priority_queue<P, vector<P>, greater<P>> minHeap;
        priority_queue<P> maxHeap;

        for (int i = 0; i < n; ++i) {
            minHeap.push({tokens[i], i});
            maxHeap.push({tokens[i], i});
        }

        vector<bool> used(n, false);
        int remaining = n;
        int score = 0;
        int bestScore = 0;

        while (remaining > 0) {
            while (!minHeap.empty() && used[minHeap.top().second]) {
                minHeap.pop();
            }
            while (!maxHeap.empty() && used[maxHeap.top().second]) {
                maxHeap.pop();
            }

            if (!minHeap.empty() && power >= minHeap.top().first) {
                int idx = minHeap.top().second;
                minHeap.pop();

                if (used[idx]) continue;
                used[idx] = true;
                --remaining;

                power -= tokens[idx];
                ++score;
                bestScore = max(bestScore, score);
            } else if (score > 0 && !maxHeap.empty()) {
                int idx = maxHeap.top().second;
                maxHeap.pop();

                if (used[idx]) continue;
                used[idx] = true;
                --remaining;

                power += tokens[idx];
                --score;
            } else {
                break;
            }
        }

        return bestScore;
    }
};

// -----------------------------------------------------------------------------
// 7. MULTISET GREEDY
// Keep remaining token values ordered. Erase the smallest for face-up;
// erase the largest for face-down.
// Time: O(n log n), Space: O(n).
// -----------------------------------------------------------------------------
class Solution7_Multiset {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        multiset<int> remaining(tokens.begin(), tokens.end());

        int score = 0;
        int bestScore = 0;

        while (!remaining.empty()) {
            auto smallest = remaining.begin();

            if (power >= *smallest) {
                power -= *smallest;
                remaining.erase(smallest);
                ++score;
                bestScore = max(bestScore, score);
            } else if (score > 0) {
                auto largest = prev(remaining.end());
                power += *largest;
                remaining.erase(largest);
                --score;
            } else {
                break;
            }
        }

        return bestScore;
    }
};

// -----------------------------------------------------------------------------
// 8. COMPACT SORTED-ARRAY GREEDY
// Same algorithm as #4, written with a single early-stop condition.
// This is a style variation, not a different asymptotic approach.
// -----------------------------------------------------------------------------
class Solution8_CompactGreedy {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        sort(tokens.begin(), tokens.end());

        int i = 0;
        int j = (int)tokens.size() - 1;
        int score = 0;
        int answer = 0;

        while (i <= j) {
            if (power >= tokens[i]) {
                power -= tokens[i++];
                answer = max(answer, ++score);
            } else if (score > 0 && i < j) {
                power += tokens[j--];
                --score;
            } else {
                break;
            }
        }

        return answer;
    }
};

/*
WHY GREEDY IS CORRECT
- When gaining score is possible, using the cheapest remaining token is
  optimal: it spends the least power for the same +1 score.
- If no remaining token is affordable, spending one score to regain power
  is the only way to continue. Selling the most expensive remaining token
  maximizes the power gained for that -1 score.
- A face-down move is useful only when there is a remaining token other than
  the one we would otherwise need to use face-up; if only one token remains
  and it is unaffordable, selling it cannot lead to a later score gain.
- Track `bestScore`, not just the final `score`, because a face-down move
  decreases the current score.

IMPORTANT FIX IN THE USER'S SUBMITTED CODE
Your `else` branch unconditionally plays a token face-down:
    power += tokens[j--];
    score--;
That is illegal when `score == 0`. Add a condition:
    else if (score > 0) { ... }
    else { break; }

Also use:
    bestScore = max(bestScore, score);
rather than relying on assignment, even though score only increases in the
face-up branch in the usual flow.

COMPLEXITY SUMMARY
1. Brute DFS                 Exponential       O(n) recursion
2. Memoized bitmask DFS      Exponential       Exponential memo
3. BFS state exploration     Exponential       Exponential visited
4. Sort + two pointers       O(n log n)        O(1) auxiliary*
5. Sort + deque              O(n log n)        O(n)
6. Two heaps                 O(n log n)        O(n)
7. Multiset                  O(n log n)        O(n)
8. Compact two pointers      O(n log n)        O(1) auxiliary*

*Sorting may use implementation-dependent stack space.
For LeetCode constraints (n <= 1000), approaches 4–8 are feasible.
Recommended submission: Solution4_TwoPointers.
*/
