/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        

        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* prev = dummy; // node just before left place node

        for(int i=1; i<left; i++) {
            prev = prev->next;
        }

        ListNode* curr = prev->next;

        for(int i=1; i<=right-left; i++) {
            ListNode* temp = prev->next;
            prev->next = curr->next;
            curr->next = curr->next->next;
            prev->next->next = temp;
        }

        return dummy->next;

    }
};

/*
LeetCode 92 — Reverse Linked List II
All major solution approaches in C++.

Problem:
Reverse the nodes from position left to position right (1-indexed), leaving
the rest of the linked list unchanged.

LeetCode provides the ListNode definition.

Approaches:
1. Brute force using an array of node pointers.
2. Two-pass approach: locate the sublist, reverse it, reconnect it.
3. One-pass in-place head-insertion technique (recommended).
4. Recursive reversal of the selected range.
5. Recursive helper that reverses the first right nodes and tracks left.

The standard optimal solution is Approach 3: O(n) time and O(1) extra space.
*/

#include <vector>
using namespace std;

/*
For local compilation only, if LeetCode does not provide ListNode:
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
*/

// -----------------------------------------------------------------------------
// APPROACH 1: Brute force with an array of node pointers
// Time: O(n)
// Extra space: O(n)
//
// Save all node addresses in a vector, reverse the pointer order for the
// requested positions, then reconnect the nodes. Node values are not copied
// or swapped; the actual nodes are reordered.
// -----------------------------------------------------------------------------
class SolutionArray {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head == nullptr || left == right) return head;

        vector<ListNode*> nodes;
        ListNode* current = head;

        while (current != nullptr) {
            nodes.push_back(current);
            current = current->next;
        }

        int l = left - 1;
        int r = right - 1;

        while (l < r) {
            ListNode* temp = nodes[l];
            nodes[l] = nodes[r];
            nodes[r] = temp;
            ++l;
            --r;
        }

        int i = 0;
        while (i + 1 < static_cast<int>(nodes.size())) {
            nodes[i]->next = nodes[i + 1];
            ++i;
        }
        nodes.back()->next = nullptr;

        return nodes[0];
    }
};

// -----------------------------------------------------------------------------
// APPROACH 2: Two-pass in-place reversal
// Time: O(n)
// Extra space: O(1)
//
// First locate the node before `left` and the first node in the segment.
// Reverse the segment with the standard three-pointer method, then reconnect.
// -----------------------------------------------------------------------------
class SolutionTwoPass {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head == nullptr || left == right) return head;

        ListNode* before = nullptr;
        ListNode* segmentStart = head;
        int position = 1;

        while (position < left) {
            before = segmentStart;
            segmentStart = segmentStart->next;
            ++position;
        }

        ListNode* previous = nullptr;
        ListNode* current = segmentStart;
        int count = left;

        while (count <= right) {
            ListNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
            ++count;
        }

        // `previous` is the new head of the reversed segment.
        if (before != nullptr) {
            before->next = previous;
        } else {
            head = previous;
        }

        // `segmentStart` is now the tail of the reversed segment.
        segmentStart->next = current;

        return head;
    }
};

// -----------------------------------------------------------------------------
// APPROACH 3: One-pass head insertion (RECOMMENDED)
// Time: O(n) (the reversal itself takes O(right - left) pointer operations)
// Extra space: O(1)
//
// Use a dummy node so the same logic works when left == 1.
// Keep `before` fixed at the node immediately before the reversed segment.
// Repeatedly take the node after `current` and insert it immediately after
// `before`. This reverses the selected segment in-place.
// -----------------------------------------------------------------------------
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head == nullptr || left == right) return head;

        ListNode dummy(0);
        dummy.next = head;

        ListNode* before = &dummy;
        int position = 1;

        while (position < left) {
            before = before->next;
            ++position;
        }

        ListNode* current = before->next;
        int moves = right - left;

        while (moves > 0) {
            ListNode* nodeToMove = current->next;

            current->next = nodeToMove->next;
            nodeToMove->next = before->next;
            before->next = nodeToMove;

            --moves;
        }

        return dummy.next;
    }
};

// -----------------------------------------------------------------------------
// APPROACH 4: Recursive reversal of the selected segment
// Time: O(n)
// Extra space: O(right - left) recursion stack for reversing the segment,
//              plus O(left) stack frames to reach the segment.
// -----------------------------------------------------------------------------
class SolutionRecursive {
private:
    ListNode* successor = nullptr;

    // Reverse the first `count` nodes and remember the node after them.
    ListNode* reverseFirstN(ListNode* head, int count) {
        if (count == 1) {
            successor = head->next;
            return head;
        }

        ListNode* newHead = reverseFirstN(head->next, count - 1);
        head->next->next = head;
        head->next = successor;
        return newHead;
    }

    ListNode* reverseFrom(ListNode* head, int left, int right) {
        if (left == 1) {
            return reverseFirstN(head, right);
        }

        head->next = reverseFrom(head->next, left - 1, right - 1);
        return head;
    }

public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head == nullptr || left == right) return head;
        successor = nullptr;
        return reverseFrom(head, left, right);
    }
};

// -----------------------------------------------------------------------------
// APPROACH 5: Recursive range reversal with explicit bounds
// Time: O(n)
// Extra space: O(n) recursion stack.
//
// This version recursively reaches the left position, then reverses the
// selected segment while unwinding. It is included as an alternative
// recursive formulation; iterative solutions are generally easier to debug.
// -----------------------------------------------------------------------------
class SolutionRecursiveRange {
private:
    ListNode* reverseRange(ListNode* current, int remaining, ListNode* after) {
        if (remaining == 0) return after;

        ListNode* nextNode = current->next;
        current->next = after;
        return reverseRange(nextNode, remaining - 1, current);
    }

    ListNode* solve(ListNode* head, int left, int right) {
        if (left == 1) {
            ListNode* segmentTail = head;
            int steps = right - 1;
            while (steps > 0) {
                segmentTail = segmentTail->next;
                --steps;
            }

            ListNode* after = segmentTail->next;
            return reverseRange(head, right, after);
        }

        head->next = solve(head->next, left - 1, right - 1);
        return head;
    }

public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head == nullptr || left == right) return head;
        return solve(head, left, right);
    }
};

/*
COMPLEXITY COMPARISON
+--------------------------------------+----------+------------------+
| Approach                             | Time     | Auxiliary space  |
+--------------------------------------+----------+------------------+
| 1. Array of node pointers             | O(n)     | O(n)             |
| 2. Two-pass iterative reversal        | O(n)     | O(1)             |
| 3. One-pass head insertion            | O(n)     | O(1)             |
| 4. Recursive first-N reversal         | O(n)     | O(n) stack       |
| 5. Recursive range reversal           | O(n)     | O(n) stack       |
+--------------------------------------+----------+------------------+

KEY INSIGHT
Only the links inside the range need to change. The nodes before `left` and
after `right` stay in the same relative order.

Example:
1 -> 2 -> 3 -> 4 -> 5, left = 2, right = 4
Result:
1 -> 4 -> 3 -> 2 -> 5

RECOMMENDATION
Submit the class named `Solution` (Approach 3). It uses a dummy node and
head insertion to reverse the range in-place with O(1) auxiliary space.
*/
