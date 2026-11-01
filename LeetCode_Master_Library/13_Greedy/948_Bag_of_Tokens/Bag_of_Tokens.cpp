/*
LeetCode 948 — Bag of Tokens
Original source: Greedy Algorithm/948. Bag of Tokens.cpp
Original source files: 1
Approaches implemented: 3
Recommended: SolutionGreedy

Approach index:
1. Exhaustive DFS over legal token plays (tiny n)
2. Memoized state search over (used mask, power, score)
3. Sort + two pointers greedy
*/

#include <algorithm>
#include <climits>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 1. Exhaustive DFS.
// Time: exponential; up to O(n! * 2^n) loose upper bound.
// Auxiliary space: O(n) recursion depth.
// Small-input correctness baseline.
class SolutionBruteForce {
    int n;
    int best;

    void dfs(const vector<int>& tokens, vector<char>& used, long long power,
             int score, int played) {
        best = max(best, score);
        if (played == n) return;

        for (int i = 0; i < n; ++i) {
            if (used[i]) continue;
            used[i] = true;
            if (power >= tokens[i]) {
                dfs(tokens, used, power - tokens[i], score + 1, played + 1);
            }
            if (score > 0) {
                dfs(tokens, used, power + tokens[i], score - 1, played + 1);
            }
            used[i] = false;
        }
    }

public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        n = (int)tokens.size();
        best = 0;
        vector<char> used(n, false);
        dfs(tokens, used, power, 0, 0);
        return best;
    }
};

// 2. Memoized state search.
// State includes mask, power, and score: mask alone is insufficient because
// different play orientations/orders produce different resource balances.
// Time/space are proportional to reachable states times O(n) transitions;
// worst case remains exponential.
class SolutionMemoization {
    struct Key {
        int mask;
        long long power;
        int score;
        bool operator==(const Key& other) const {
            return mask == other.mask && power == other.power &&
                   score == other.score;
        }
    };

    struct KeyHash {
        size_t operator()(const Key& key) const {
            size_t h = hash<int>{}(key.mask);
            h ^= hash<long long>{}(key.power) + 0x9e3779b9 + (h << 6) +
                 (h >> 2);
            h ^= hash<int>{}(key.score) + 0x9e3779b9 + (h << 6) + (h >> 2);
            return h;
        }
    };

    const vector<int>* tokens;
    int n;
    unordered_map<Key, int, KeyHash> memo;

    int dfs(int mask, long long power, int score) {
        Key key{mask, power, score};
        auto found = memo.find(key);
        if (found != memo.end()) return found->second;

        int answer = score;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) continue;
            const int nextMask = mask | (1 << i);
            if (power >= (*tokens)[i]) {
                answer = max(answer,
                             dfs(nextMask, power - (*tokens)[i], score + 1));
            }
            if (score > 0) {
                answer = max(answer,
                             dfs(nextMask, power + (*tokens)[i], score - 1));
            }
        }
        memo.emplace(key, answer);
        return answer;
    }

public:
    int bagOfTokensScore(vector<int>& input, int power) {
        n = (int)input.size();
        if (n > 20) return -1;
        tokens = &input;
        memo.clear();
        return dfs(0, power, 0);
    }
};

// 3. Sort + two-pointer greedy.
// Buy the cheapest affordable token face-up; when stuck, sell the most
// expensive remaining token face-down to gain the most power.
// Time: O(n log n); auxiliary space: O(log n) sorting stack.
class SolutionGreedy {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        sort(tokens.begin(), tokens.end());
        int left = 0;
        int right = (int)tokens.size() - 1;
        int score = 0;
        int best = 0;
        long long currentPower = power;

        while (left <= right) {
            if (currentPower >= tokens[left]) {
                currentPower -= tokens[left++];
                best = max(best, ++score);
            } else if (score > 0 && left < right) {
                currentPower += tokens[right--];
                --score;
            } else {
                break;
            }
        }
        return best;
    }
};
