#include <bits/stdc++.h>
using namespace std;

/*
LeetCode 2410 — Maximum Matching of Players With Trainers
(Same greedy problem as LeetCode 455 — Assign Cookies)

Required signature:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers)

Approaches included:
1. Sort both arrays + two pointers (optimal greedy)
2. Sort + binary search for the largest feasible prefix (same matching count)
3. Sort + lower_bound for each player (equivalent greedy formulation)
4. Brute force backtracking (exponential; for learning only)
5. General bipartite matching (Kuhn's algorithm; more general but slower)

Let p = players.size(), t = trainers.size(), N = p + t.
For this problem, Approach 1 is recommended: O(p log p + t log t), O(1)
extra space excluding sorting implementation details.
*/

class Solution {
private:
    // ---------------------------------------------------------------
    // Approach 4 helper: Brute force backtracking.
    // At each player, either skip them or assign an unused suitable trainer.
    // Exponential; only use for tiny test cases.
    // ---------------------------------------------------------------
    int bruteForceDfs(const vector<int>& players,
                      const vector<int>& trainers,
                      int i,
                      vector<bool>& used) {
        if (i == (int)players.size()) return 0;

        int best = bruteForceDfs(players, trainers, i + 1, used); // Skip player.

        for (int j = 0; j < (int)trainers.size(); ++j) {
            if (!used[j] && players[i] <= trainers[j]) {
                used[j] = true;
                best = max(best, 1 + bruteForceDfs(players, trainers, i + 1, used));
                used[j] = false;
            }
        }

        return best;
    }

    // ---------------------------------------------------------------
    // Approach 5 helper: Kuhn's algorithm for bipartite matching.
    // This version is general-purpose, but O(p * t) in the worst case.
    // ---------------------------------------------------------------
    bool tryMatch(int player,
                  const vector<int>& players,
                  const vector<int>& trainers,
                  vector<int>& trainerToPlayer,
                  vector<bool>& visited) {
        for (int j = 0; j < (int)trainers.size(); ++j) {
            if (visited[j] || players[player] > trainers[j]) continue;

            visited[j] = true;

            if (trainerToPlayer[j] == -1 ||
                tryMatch(trainerToPlayer[j], players, trainers,
                         trainerToPlayer, visited)) {
                trainerToPlayer[j] = player;
                return true;
            }
        }

        return false;
    }

public:
    // Default LeetCode solution: sort + two pointers.
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        return matchPlayersAndTrainersTwoPointers(players, trainers);
    }

    // ---------------------------------------------------------------
    // Approach 1: Sort both arrays + two pointers (BEST).
    //
    // Match the weakest remaining player with the weakest trainer who
    // can train them. If the trainer is too weak, discard that trainer.
    //
    // Time: O(p log p + t log t)
    // Extra space: O(1) auxiliary, excluding sorting implementation details.
    // ---------------------------------------------------------------
    int matchPlayersAndTrainersTwoPointers(vector<int>& players,
                                           vector<int>& trainers) {
        sort(players.begin(), players.end());
        sort(trainers.begin(), trainers.end());

        int p = (int)players.size();
        int t = (int)trainers.size();
        int i = 0, j = 0;
        int answer = 0;

        while (i < p && j < t) {
            if (players[i] <= trainers[j]) {
                // This trainer can handle this player; use both.
                ++answer;
                ++i;
                ++j;
            } else {
                // This trainer cannot handle the weakest remaining player,
                // so they cannot handle any remaining player either.
                ++j;
            }
        }

        return answer;
    }

    // ---------------------------------------------------------------
    // Approach 2: Sort + binary search on the answer.
    //
    // For a candidate count x, the x weakest players can be matched with
    // the x strongest trainers if players[i] <= trainers[t - x + i].
    // Feasibility is monotonic, so binary search for the maximum x.
    //
    // Time: O(p log p + t log t + min(p,t) log(min(p,t)))
    // Space: O(1) auxiliary, excluding sorting details.
    // ---------------------------------------------------------------
    int matchPlayersAndTrainersBinarySearch(vector<int>& players,
                                            vector<int>& trainers) {
        sort(players.begin(), players.end());
        sort(trainers.begin(), trainers.end());

        int p = (int)players.size();
        int t = (int)trainers.size();
        int low = 0, high = min(p, t);

        auto canMatch = [&](int count) {
            // Pair the count weakest players with the count strongest trainers.
            for (int i = 0; i < count; ++i) {
                if (players[i] > trainers[t - count + i]) {
                    return false;
                }
            }
            return true;
        };

        while (low < high) {
            int mid = low + (high - low + 1) / 2;

            if (canMatch(mid)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }

        return low;
    }

    // ---------------------------------------------------------------
    // Approach 3: Sort + lower_bound for each player.
    //
    // For each player in ascending order, find the smallest trainer
    // capacity >= that player's ability among the remaining trainers.
    // This is the same earliest-feasible matching greedy.
    //
    // Time: O(p log p + t log t + p log t), Space: O(1) auxiliary.
    // ---------------------------------------------------------------
    int matchPlayersAndTrainersLowerBound(vector<int>& players,
                                          vector<int>& trainers) {
        sort(players.begin(), players.end());
        sort(trainers.begin(), trainers.end());

        int answer = 0;
        auto it = trainers.begin();

        for (int ability : players) {
            it = lower_bound(it, trainers.end(), ability);

            if (it == trainers.end()) break;

            ++answer;
            ++it; // This trainer is now used.
        }

        return answer;
    }

    // ---------------------------------------------------------------
    // Approach 4: Brute force backtracking.
    // Exponential; only for small inputs and conceptual understanding.
    // ---------------------------------------------------------------
    int matchPlayersAndTrainersBruteForce(vector<int>& players,
                                          vector<int>& trainers) {
        vector<bool> used(trainers.size(), false);
        return bruteForceDfs(players, trainers, 0, used);
    }

    // ---------------------------------------------------------------
    // Approach 5: General bipartite matching (Kuhn's algorithm).
    // Useful for arbitrary compatibility graphs; overkill for this problem.
    // Time: O(p * t * min(p,t)) as a safe bound for this implementation;
    // often described as O(VE) for Kuhn's algorithm.
    // Space: O(t + recursion depth).
    // ---------------------------------------------------------------
    int matchPlayersAndTrainersBipartite(vector<int>& players,
                                         vector<int>& trainers) {
        int p = (int)players.size();
        int t = (int)trainers.size();

        vector<int> trainerToPlayer(t, -1);
        int answer = 0;

        for (int i = 0; i < p; ++i) {
            vector<bool> visited(t, false);
            if (tryMatch(i, players, trainers, trainerToPlayer, visited)) {
                ++answer;
            }
        }

        return answer;
    }
};

/*
Example:
players  = {4, 7, 9}
trainers = {8, 2, 5, 8}
Answer   = 2

Why two pointers work:
After sorting, if the smallest remaining trainer cannot train the smallest
remaining player, that trainer cannot train any other remaining player.
Otherwise, matching these two is safe: it uses the smallest capable trainer
for the weakest player and preserves stronger trainers for stronger players.

For submission, use Approach 1.
*/
