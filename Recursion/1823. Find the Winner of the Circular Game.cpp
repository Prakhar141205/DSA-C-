/*
LeetCode 1823: Find the Winner of the Circular Game
Approaches from brute force to optimal.

The answer is 1-indexed (friends are numbered 1..n).
Copy ONE SolutionN class and rename it to Solution before submitting.
*/
#include <bits/stdc++.h>
using namespace std;

/*
APPROACH 1: Brute force simulation using a vector
- Keep the currently alive friends in a vector.
- Starting at the current index, remove every k-th friend.
- After removing a friend, the next counting starts at the index that
  shifted into the removed position.

Time: O(n^2) because vector erase shifts elements.
Space: O(n).
*/
class Solution1 {
public:
    int findTheWinner(int n, int k) {
        vector<int> friends;
        for (int i = 1; i <= n; ++i) friends.push_back(i);

        int index = 0;
        while (friends.size() > 1) {
            index = (index + k - 1) % friends.size();
            friends.erase(friends.begin() + index);
        }

        return friends[0];
    }
};

/*
APPROACH 2: Brute force simulation using a queue
- Rotate the first k-1 friends to the back.
- Remove the k-th friend at the front.
- Repeat until one friend remains.

Time: O(n*k), with k <= n, so O(n^2) worst case.
Space: O(n).
*/
class Solution2 {
public:
    int findTheWinner(int n, int k) {
        queue<int> q;
        for (int i = 1; i <= n; ++i) q.push(i);

        while (q.size() > 1) {
            int count = 1;
            while (count < k) {
                q.push(q.front());
                q.pop();
                ++count;
            }
            q.pop();
        }

        return q.front();
    }
};

/*
APPROACH 3: Recursive Josephus recurrence
Let f(n) be the winner's zero-based index among n friends.
Base case: f(1) = 0.
Recurrence: f(n) = (f(n - 1) + k) % n.
Convert the final zero-based answer to 1-based by adding 1.

Time: O(n)
Space: O(n) recursion stack.
*/
class Solution3 {
private:
    int josephus(int n, int k) {
        if (n == 1) return 0;
        return (josephus(n - 1, k) + k) % n;
    }

public:
    int findTheWinner(int n, int k) {
        return josephus(n, k) + 1;
    }
};

/*
APPROACH 4: Iterative Josephus recurrence (OPTIMAL)
- Build the answer for circle sizes 1, 2, ..., n.
- Keep only the current winner's zero-based index.

Time: O(n)
Auxiliary space: O(1)
This satisfies the follow-up.
*/
class Solution4 {
public:
    int findTheWinner(int n, int k) {
        int winner = 0; // winner for a circle of size 1, zero-based

        int size = 2;
        while (size <= n) {
            winner = (winner + k) % size;
            ++size;
        }

        return winner + 1;
    }
};

/*
COMPLEXITY SUMMARY

Approach 1: Vector simulation       O(n^2) time, O(n) space
Approach 2: Queue simulation        O(n*k) time, O(n) space
Approach 3: Recursive recurrence    O(n) time, O(n) stack
Approach 4: Iterative recurrence    O(n) time, O(1) extra space

Recommended: Approach 4.
*/
