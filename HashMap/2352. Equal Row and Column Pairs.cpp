#include <bits/stdc++.h>
using namespace std;

/*
    LeetCode 2352 - Equal Row and Column Pairs

    Count ordered pairs (rowIndex, columnIndex) where the row and column
    contain exactly the same values in the same order.

    All classes below are independent implementations. Rename the chosen
    class to Solution before submitting to LeetCode.
*/

// Approach 1 Using Trie
class Solution {
    struct TrieNode {
        unordered_map<int, TrieNode*> children;
        int count = 0;
    };

    TrieNode* root;

    void insert(vector<int>& row) {
        TrieNode* node = root;

        for (int x : row) {
            if (!node->children.count(x)) {
                node->children[x] = new TrieNode();
            }

            node = node->children[x];
        }

        node->count++;
    }

    int search(vector<int>& col) {
        TrieNode* node = root;

        for (int x : col) {
            if (!node->children.count(x)) {
                return 0;
            }

            node = node->children[x];
        }

        return node->count;
    }

public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = grid.size();
        root = new TrieNode();

        // Insert all rows.
        for (auto& row : grid) {
            insert(row);
        }

        int ans = 0;

        // Search all columns.
        for (int j = 0; j < n; j++) {
            vector<int> col;

            for (int i = 0; i < n; i++) {
                col.push_back(grid[i][j]);
            }

            ans += search(col);
        }

        return ans;
    }
};
// -----------------------------------------------------------------------------
// Approach 1: Brute force
// Time: O(n^3); Space: O(1) auxiliary.
// Compare every row with every column, checking all n positions.
// -----------------------------------------------------------------------------
class SolutionBruteForce {
public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = (int)grid.size();
        int answer = 0;

        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                bool equal = true;

                for (int k = 0; k < n; ++k) {
                    if (grid[row][k] != grid[k][col]) {
                        equal = false;
                        break;
                    }
                }

                if (equal) ++answer;
            }
        }

        return answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 2: Store rows in a map, then build and query each column
// Time: O(n^2 log n); Space: O(n^2).
// The map stores how many times each row vector occurs. Every matching column
// contributes the frequency of its vector, so duplicate rows are counted.
// -----------------------------------------------------------------------------
class SolutionOrderedMap {
public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = (int)grid.size();

        map<vector<int>, int> rowFrequency;

        for (const auto& row : grid) {
            ++rowFrequency[row];
        }

        int answer = 0;

        for (int col = 0; col < n; ++col) {
            vector<int> column;
            column.reserve(n);

            for (int row = 0; row < n; ++row) {
                column.push_back(grid[row][col]);
            }

            auto it = rowFrequency.find(column);
            if (it != rowFrequency.end()) {
                answer += it->second;
            }
        }

        return answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 3: Store rows in an unordered_map with a custom vector hash
// Average Time: O(n^2); Space: O(n^2).
// Hash collisions are handled by unordered_map's equality comparison.
// -----------------------------------------------------------------------------
struct VectorHash {
    size_t operator()(const vector<int>& values) const {
        size_t seed = values.size();

        for (int value : values) {
            seed ^= hash<int>{}(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        return seed;
    }
};

class SolutionUnorderedMap {
public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = (int)grid.size();

        unordered_map<vector<int>, int, VectorHash> rowFrequency;
        rowFrequency.reserve(n * 2);

        for (const auto& row : grid) {
            ++rowFrequency[row];
        }

        int answer = 0;

        for (int col = 0; col < n; ++col) {
            vector<int> column;
            column.reserve(n);

            for (int row = 0; row < n; ++row) {
                column.push_back(grid[row][col]);
            }

            auto it = rowFrequency.find(column);
            if (it != rowFrequency.end()) {
                answer += it->second;
            }
        }

        return answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 4: Encode each row/column as a string key
// Time: O(n^2); Space: O(n^2).
// Values are positive and <= 1e5. Delimiters prevent ambiguous encodings.
// Example: [1, 23] -> "1#23#", not "123".
// -----------------------------------------------------------------------------
class SolutionStringEncoding {
private:
    string encode(const vector<int>& values) {
        string key;

        for (int value : values) {
            key += to_string(value);
            key += '#';
        }

        return key;
    }

public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = (int)grid.size();

        unordered_map<string, int> rowFrequency;
        rowFrequency.reserve(n * 2);

        for (const auto& row : grid) {
            ++rowFrequency[encode(row)];
        }

        int answer = 0;

        for (int col = 0; col < n; ++col) {
            string key;

            for (int row = 0; row < n; ++row) {
                key += to_string(grid[row][col]);
                key += '#';
            }

            auto it = rowFrequency.find(key);
            if (it != rowFrequency.end()) {
                answer += it->second;
            }
        }

        return answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 5: Sort rows and columns as pairs of (value, position)
// Time: O(n^2 log n); Space: O(n).
// This is an alternative representation that preserves order by including
// each element's index. It is mainly educational; hashing vectors is simpler.
// -----------------------------------------------------------------------------
class SolutionPositionAwareSorting {
public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = (int)grid.size();
        map<vector<pair<int, int>>, int> rowFrequency;

        for (int r = 0; r < n; ++r) {
            vector<pair<int, int>> key;
            key.reserve(n);

            for (int c = 0; c < n; ++c) {
                key.push_back({grid[r][c], c});
            }

            ++rowFrequency[key];
        }

        int answer = 0;

        for (int c = 0; c < n; ++c) {
            vector<pair<int, int>> key;
            key.reserve(n);

            for (int r = 0; r < n; ++r) {
                key.push_back({grid[r][c], r});
            }

            // The position labels here must correspond to sequence positions,
            // not matrix row IDs. Rebuild a normalized sequence key instead.
            vector<int> column;
            column.reserve(n);
            for (int r = 0; r < n; ++r) {
                column.push_back(grid[r][c]);
            }

            vector<pair<int, int>> normalized;
            normalized.reserve(n);
            for (int i = 0; i < n; ++i) {
                normalized.push_back({column[i], i});
            }

            auto it = rowFrequency.find(normalized);
            if (it != rowFrequency.end()) {
                answer += it->second;
            }
        }

        return answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 6: Direct row-frequency array via serialized keys + ordered map
// Time: O(n^2 log n); Space: O(n^2).
// This variant uses a canonical delimiter-separated string key and std::map.
// -----------------------------------------------------------------------------
class SolutionOrderedStringMap {
private:
    string makeKey(const vector<int>& values) {
        string key;
        for (int x : values) {
            key += to_string(x);
            key.push_back(',');
        }
        return key;
    }

public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = (int)grid.size();
        map<string, int> rowFrequency;

        for (const auto& row : grid) {
            ++rowFrequency[makeKey(row)];
        }

        int answer = 0;

        for (int c = 0; c < n; ++c) {
            string key;

            for (int r = 0; r < n; ++r) {
                key += to_string(grid[r][c]);
                key.push_back(',');
            }

            auto it = rowFrequency.find(key);
            if (it != rowFrequency.end()) {
                answer += it->second;
            }
        }

        return answer;
    }
};


/*
    Example 1:
      grid = [[3,2,1],
              [1,7,6],
              [2,7,7]]

      Rows:
        R0 = [3,2,1]
        R1 = [1,7,6]
        R2 = [2,7,7]

      Columns:
        C0 = [3,1,2]
        C1 = [2,7,7]
        C2 = [1,6,7]

      Only R2 == C1, so answer = 1.

    Example 2:
      grid = [[3,1,2,2],
              [1,4,4,5],
              [2,4,2,2],
              [2,4,2,2]]

      [3,1,2,2] occurs as row 0 and column 0.
      [2,4,2,2] occurs as rows 2 and 3, and column 2.
      Total pairs = 1 + 2 = 3.

    Important:
      - Order matters. Do NOT sort row/column values before comparing.
      - Duplicate rows/columns matter. Store frequencies, not just presence.
      - Approach 5 is an educational positional-key variation; Approach 2,
        3, or 4 is preferable in practice.

    Recommended:
      - Approach 3: vector key + custom hash, average O(n^2).
      - Approach 4: string encoding, also average O(n^2), easy to implement.
*/
