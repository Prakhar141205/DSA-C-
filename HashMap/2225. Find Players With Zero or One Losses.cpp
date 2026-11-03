#include <bits/stdc++.h>
using namespace std;

/*
    LeetCode 2225 - Find Players With Zero or One Losses

    answer[0]: players with zero losses, increasing order.
    answer[1]: players with exactly one loss, increasing order.

    All implementations are independent. Rename the chosen class to Solution
    before submitting to LeetCode.
*/


// 1. Brute force: collect distinct players, then scan all matches per player.
// Time: O(P log P + P*n); Space: O(P), where P is distinct player count.
class SolutionBruteForce {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        vector<int> players;

        for (const auto& match : matches) {
            players.push_back(match[0]);
            players.push_back(match[1]);
        }

        sort(players.begin(), players.end());
        players.erase(unique(players.begin(), players.end()), players.end());

        vector<vector<int>> answer(2);

        for (int player : players) {
            int lossCount = 0;

            for (const auto& match : matches) {
                if (match[1] == player) ++lossCount;
            }

            if (lossCount == 0) answer[0].push_back(player);
            else if (lossCount == 1) answer[1].push_back(player);
        }

        return answer;
    }
};


// 2. Two ordered maps: winner appearances and loser counts.
// Time: O(n log P); Space: O(P). Map traversal is already sorted.
class SolutionTwoMaps {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        map<int, int> winnerCount;
        map<int, int> lossCount;

        for (const auto& match : matches) {
            ++winnerCount[match[0]];
            ++lossCount[match[1]];
        }

        vector<vector<int>> answer(2);

        for (const auto& [player, wins] : winnerCount) {
            (void)wins;
            if (lossCount.find(player) == lossCount.end()) {
                answer[0].push_back(player);
            }
        }

        for (const auto& [player, losses] : lossCount) {
            if (losses == 1) answer[1].push_back(player);
        }

        return answer;
    }
};


// 3. One ordered map storing each appearing player's loss count.
// Time: O(n log P); Space: O(P). Automatically sorted output.
class SolutionOneMap {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        map<int, int> losses;

        for (const auto& match : matches) {
            int winner = match[0];
            int loser = match[1];

            losses.try_emplace(winner, 0); // Register winner with zero losses.
            ++losses[loser];              // Count this player's loss.
        }

        vector<vector<int>> answer(2);

        for (const auto& [player, count] : losses) {
            if (count == 0) answer[0].push_back(player);
            else if (count == 1) answer[1].push_back(player);
        }

        return answer;
    }
};


// 4. Unordered map + sort the answer lists.
// Average Time: O(n + P log P); Space: O(P).
class SolutionHashMap {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        unordered_map<int, int> losses;
        losses.reserve(matches.size() * 2);

        for (const auto& match : matches) {
            losses.try_emplace(match[0], 0);
            ++losses[match[1]];
        }

        vector<vector<int>> answer(2);

        for (const auto& [player, count] : losses) {
            if (count == 0) answer[0].push_back(player);
            else if (count == 1) answer[1].push_back(player);
        }

        sort(answer[0].begin(), answer[0].end());
        sort(answer[1].begin(), answer[1].end());

        return answer;
    }
};


// 5. Fixed-size frequency array; player IDs are in [1, 100000].
// Time: O(n + U); Space: O(U), U = 100000.
// State -1: unseen, 0: zero losses, 1: one loss, 2: two or more losses.
class SolutionFrequencyArray {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        const int MAX_PLAYER = 100000;
        vector<int> losses(MAX_PLAYER + 1, -1);

        for (const auto& match : matches) {
            int winner = match[0];
            int loser = match[1];

            if (losses[winner] == -1) losses[winner] = 0;

            if (losses[loser] == -1) losses[loser] = 1;
            else if (losses[loser] < 2) ++losses[loser];
        }

        vector<vector<int>> answer(2);

        // Scanning IDs in ascending order gives sorted output.
        for (int player = 1; player <= MAX_PLAYER; ++player) {
            if (losses[player] == 0) answer[0].push_back(player);
            else if (losses[player] == 1) answer[1].push_back(player);
        }

        return answer;
    }
};


// 6. Coordinate compression + vector of loss counts.
// Time: O(n log P); Space: O(P).
// Useful when IDs are large/arbitrary and a fixed-size array is undesirable.
class SolutionCoordinateCompression {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        vector<int> players;
        players.reserve(matches.size() * 2);

        for (const auto& match : matches) {
            players.push_back(match[0]);
            players.push_back(match[1]);
        }

        sort(players.begin(), players.end());
        players.erase(unique(players.begin(), players.end()), players.end());

        vector<int> losses(players.size(), 0);

        for (const auto& match : matches) {
            int loser = match[1];
            int index = (int)(lower_bound(players.begin(), players.end(), loser)
                              - players.begin());
            ++losses[index];
        }

        vector<vector<int>> answer(2);

        for (int i = 0; i < (int)players.size(); ++i) {
            if (losses[i] == 0) answer[0].push_back(players[i]);
            else if (losses[i] == 1) answer[1].push_back(players[i]);
        }

        return answer;
    }
};


/*
    Dry run:
      matches = [[1,3],[2,3],[3,6],[5,6],[5,7],
                 [4,5],[4,8],[4,9],[10,4],[10,9]]

    Loss counts:
      1 -> 0, 2 -> 0, 3 -> 2, 4 -> 1, 5 -> 1,
      6 -> 2, 7 -> 1, 8 -> 1, 9 -> 2, 10 -> 0

    answer[0] = [1, 2, 10]
    answer[1] = [4, 5, 7, 8]

    Correctness:
      Every player is registered either as a winner or loser.
      Winners are registered with zero losses; each loser occurrence
      increments that player's loss count. Therefore, count 0 and count 1
      identify exactly the required groups.

    Recommended:
      - Approach 3: clean, concise, automatically sorted.
      - Approach 5: efficient for the given bounded player IDs.

    Your two-map approach is also correct: a player with zero losses must
    appear as a winner and must be absent from the loser map.
*/
