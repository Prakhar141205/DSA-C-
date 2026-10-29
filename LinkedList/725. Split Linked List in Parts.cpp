/*
LeetCode 725 — Split Linked List in Parts
All major solution approaches in C++.

The ListNode definition is supplied by LeetCode.

Approaches:
1. Brute force: recount remaining nodes for each part.
2. Two-pass length + direct splitting (recommended).
3. Store node pointers in an array, then cut.
4. Recursive length calculation + iterative splitting.

Let n = number of nodes and k = number of parts.
*/

#include <vector>
using namespace std;

/*
LeetCode supplies ListNode. For local compilation, use:
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
*/

// APPROACH 1: Brute force — recount the remaining nodes for every part.
// Time: O(n * k) worst case. Extra space: O(1), excluding output.
// This is simple, but repeatedly counts the same nodes.
class SolutionBruteForce {
public:
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        vector<ListNode*> result(k, nullptr);
        ListNode* current = head;

        for (int part = 0; part < k; ++part) {
            if (current == nullptr) break;

            int remaining = 0;
            for (ListNode* node = current; node != nullptr; node = node->next) {
                ++remaining;
            }

            int remainingParts = k - part;
            int partSize = (remaining + remainingParts - 1) / remainingParts;

            result[part] = current;
            for (int step = 1; step < partSize; ++step) {
                current = current->next;
            }

            ListNode* nextPart = current->next;
            current->next = nullptr;
            current = nextPart;
        }
        return result;
    }
};

// APPROACH 2: Count once, then split directly. RECOMMENDED.
// Time: O(n + k). Extra space: O(1), excluding output.
class Solution {
private:
    int getSize(ListNode* head) {
        int size = 0;
        while (head != nullptr) {
            ++size;
            head = head->next;
        }
        return size;
    }

public:
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        int n = getSize(head);
        int baseSize = n / k;
        int extra = n % k;

        vector<ListNode*> result(k, nullptr);
        ListNode* current = head;

        for (int i = 0; i < k; ++i) {
            result[i] = current;
            int partSize = baseSize + (i < extra ? 1 : 0);

            // Move to the last node in this part.
            for (int j = 1; j < partSize; ++j) {
                current = current->next;
            }

            if (current != nullptr) {
                ListNode* nextPart = current->next;
                current->next = nullptr;
                current = nextPart;
            }
        }
        return result;
    }
};

// APPROACH 3: Store every node pointer, then cut the list.
// Time: O(n + k). Extra space: O(n), for the node-pointer array.
class SolutionUsingArray {
public:
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        vector<ListNode*> nodes;
        for (ListNode* node = head; node != nullptr; node = node->next) {
            nodes.push_back(node);
        }

        int n = static_cast<int>(nodes.size());
        int baseSize = n / k;
        int extra = n % k;
        vector<ListNode*> result(k, nullptr);
        int index = 0;

        for (int i = 0; i < k; ++i) {
            int partSize = baseSize + (i < extra ? 1 : 0);
            if (partSize == 0) continue;

            result[i] = nodes[index];
            int lastIndex = index + partSize - 1;
            nodes[lastIndex]->next = nullptr;
            index += partSize;
        }
        return result;
    }
};

// APPROACH 4: Recursive length calculation, then iterative splitting.
// Time: O(n + k). Extra space: O(n) worst-case recursive call stack.
// Included for learning; it is not better than Approach 2.
class SolutionRecursiveLength {
private:
    int recursiveSize(ListNode* node) {
        if (node == nullptr) return 0;
        return 1 + recursiveSize(node->next);
    }

public:
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        int n = recursiveSize(head);
        int baseSize = n / k;
        int extra = n % k;
        vector<ListNode*> result(k, nullptr);
        ListNode* current = head;

        for (int i = 0; i < k; ++i) {
            result[i] = current;
            int partSize = baseSize + (i < extra ? 1 : 0);
            if (partSize == 0) continue;

            for (int j = 1; j < partSize; ++j) {
                current = current->next;
            }

            ListNode* nextPart = current->next;
            current->next = nullptr;
            current = nextPart;
        }
        return result;
    }
};

class Solution {
public:
    int getsize(ListNode* head) {
        int size = 0;

        while (head != nullptr) {
            size++;
            head = head->next;
        }

        return size;
    }

    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        int n = getsize(head);
        int baseSize = n / k;
        int extra = n % k;

        vector<ListNode*> ans(k, nullptr);
        ListNode* curr = head;

        int i = 0;

        while (i < k) {
            ans[i] = curr;

            int partSize = baseSize;

            if (extra > 0) {
                partSize++;
                extra--;
            }

            int j = 1;

            while (j < partSize) {
                curr = curr->next;
                j++;
            }

            if (curr != nullptr) {
                ListNode* nextPart = curr->next;
                curr->next = nullptr;
                curr = nextPart;
            }

            i++;
        }

        return ans;
    }
};

/*
COMPLEXITY COMPARISON
+-------------------------------+-------------+---------------------------+
| Approach                      | Time        | Extra space, excluding    |
|                               |             | the output vector         |
+-------------------------------+-------------+---------------------------+
| 1. Recount remaining nodes    | O(n * k)    | O(1)                      |
| 2. Count once, then split     | O(n + k)    | O(1)                      |
| 3. Store node pointers        | O(n + k)    | O(n)                      |
| 4. Recursive length + split   | O(n + k)    | O(n) call stack           |
+-------------------------------+-------------+---------------------------+

KEY INSIGHT
baseSize = n / k
extra    = n % k

Every part has baseSize nodes, and the first extra parts get one additional
node. For example, n = 10 and k = 3 gives part sizes 4, 3, 3.

EDGE CASES
- n < k: first n parts have one node each; remaining parts are nullptr.
- n is divisible by k: all parts have equal size.
- n == 0: all k parts are nullptr.

Recommended LeetCode submission: the class named Solution (Approach 2).
*/
