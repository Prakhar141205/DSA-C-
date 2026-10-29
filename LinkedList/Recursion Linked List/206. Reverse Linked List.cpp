/*
COMBINED LINKED-LIST SOLUTIONS
LeetCode 206 — Reverse Linked List
LeetCode 21  — Merge Two Sorted Lists

This file collects brute-force, alternative, and optimal approaches for both
problems. Each approach has a separate class so the methods do not conflict.

LeetCode provides the ListNode definition. If compiling locally, uncomment
and use this definition:

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

*/

#include <vector>
using namespace std;

// ============================================================================
// LEETCODE 206 — REVERSE LINKED LIST
// ============================================================================

// ---------------------------------------------------------------------------
// 206 — Approach 1: Brute force with a vector of node pointers
// Time: O(n), extra space: O(n)
// Save pointers, then reconnect them in reverse order. This rearranges the
// actual nodes rather than copying their values.
// ---------------------------------------------------------------------------
class ReverseListVector {
public:
    ListNode* reverseList(ListNode* head) {
        vector<ListNode*> nodes;
        ListNode* current = head;

        while (current != nullptr) {
            nodes.push_back(current);
            current = current->next;
        }

        if (nodes.empty()) return nullptr;

        int i = static_cast<int>(nodes.size()) - 1;
        ListNode* newHead = nodes[i];
        nodes[i]->next = nullptr;

        while (i > 0) {
            nodes[i]->next = nodes[i - 1];
            --i;
        }
        nodes[0]->next = nullptr;

        return newHead;
    }
};

// ---------------------------------------------------------------------------
// 206 — Approach 2: Iterative three-pointer reversal (optimal)
// Time: O(n), extra space: O(1)
// At every step, reverse current->next, then advance all three pointers.
// ---------------------------------------------------------------------------
class ReverseListIterative {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* previous = nullptr;
        ListNode* current = head;

        while (current != nullptr) {
            ListNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }

        return previous;
    }
};

// ---------------------------------------------------------------------------
// 206 — Approach 3: Recursive reversal (standard recursive solution)
// Time: O(n), extra space: O(n) recursion stack
// Reverse the suffix first, then point the next node back to the current node.
// ---------------------------------------------------------------------------
class ReverseListRecursive {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode* newHead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return newHead;
    }
};

// ---------------------------------------------------------------------------
// 206 — Approach 4: Recursive prefix-style reversal
// Time: O(n), extra space: O(n) recursion stack
// Recurse down the list, passing the previous node and current node.
// This is a tail-recursive-style formulation (C++ does not guarantee
// tail-call optimization).
// ---------------------------------------------------------------------------
class ReverseListRecursiveHelper {
private:
    ListNode* reverse(ListNode* previous, ListNode* current) {
        if (current == nullptr) return previous;

        ListNode* nextNode = current->next;
        current->next = previous;
        return reverse(current, nextNode);
    }

public:
    ListNode* reverseList(ListNode* head) {
        return reverse(nullptr, head);
    }
};

// ============================================================================
// LEETCODE 21 — MERGE TWO SORTED LISTS
// ============================================================================

// ---------------------------------------------------------------------------
// 21 — Approach 1: Brute force with a vector of values
// Time: O((n + m) log(n + m)), extra space: O(n + m)
// Collect values, sort them, and create a new list. This does NOT reuse the
// input nodes, so it is less suitable when the task expects splicing nodes.
// Included as a straightforward baseline.
// ---------------------------------------------------------------------------
#include <algorithm>

class MergeTwoListsBruteForce {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        vector<int> values;

        while (list1 != nullptr) {
            values.push_back(list1->val);
            list1 = list1->next;
        }
        while (list2 != nullptr) {
            values.push_back(list2->val);
            list2 = list2->next;
        }

        sort(values.begin(), values.end());

        ListNode dummy(0);
        ListNode* tail = &dummy;

        int i = 0;
        while (i < static_cast<int>(values.size())) {
            tail->next = new ListNode(values[i]);
            tail = tail->next;
            ++i;
        }

        return dummy.next;
    }
};

// ---------------------------------------------------------------------------
// 21 — Approach 2: Iterative merge using a dummy node (optimal)
// Time: O(n + m), extra space: O(1) auxiliary
// Reuses the input nodes and attaches the smaller head at each step.
// ---------------------------------------------------------------------------
class MergeTwoListsIterative {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        // At most one list still has nodes. Attach the remaining suffix.
        tail->next = (list1 != nullptr) ? list1 : list2;

        return dummy.next;
    }
};

// ---------------------------------------------------------------------------
// 21 — Approach 3: Recursive merge
// Time: O(n + m), extra space: O(n + m) recursion stack in the worst case
// The smaller current node becomes the head, and its next pointer receives
// the recursively merged remainder.
// ---------------------------------------------------------------------------
class MergeTwoListsRecursive {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;

        if (list1->val <= list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        }

        list2->next = mergeTwoLists(list1, list2->next);
        return list2;
    }
};

// ---------------------------------------------------------------------------
// 21 — Approach 4: Iterative merge without a dummy node
// Time: O(n + m), extra space: O(1) auxiliary
// Shows how to initialize the merged head separately, then append nodes.
// ---------------------------------------------------------------------------
class MergeTwoListsNoDummy {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;

        ListNode* head = nullptr;
        ListNode* tail = nullptr;

        if (list1->val <= list2->val) {
            head = tail = list1;
            list1 = list1->next;
        } else {
            head = tail = list2;
            list2 = list2->next;
        }

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        tail->next = (list1 != nullptr) ? list1 : list2;
        return head;
    }
};

/*
===============================================================================
COMPLEXITY COMPARISON
===============================================================================

LeetCode 206 — Reverse Linked List
+--------------------------------------+----------+------------------+
| Approach                             | Time     | Auxiliary space  |
+--------------------------------------+----------+------------------+
| Vector of node pointers              | O(n)     | O(n)             |
| Iterative three-pointer reversal     | O(n)     | O(1)             |
| Standard recursive reversal          | O(n)     | O(n) stack       |
| Recursive helper with prev/current   | O(n)     | O(n) stack       |
+--------------------------------------+----------+------------------+

LeetCode 21 — Merge Two Sorted Lists
+--------------------------------------+----------------------+------------------+
| Approach                             | Time                 | Auxiliary space  |
+--------------------------------------+----------------------+------------------+
| Collect values, sort, build new list | O((n+m) log(n+m))    | O(n+m)           |
| Iterative dummy-node merge           | O(n+m)               | O(1)              |
| Recursive merge                      | O(n+m)               | O(n+m) stack      |
| Iterative merge without dummy        | O(n+m)               | O(1)              |
+--------------------------------------+----------------------+------------------+

KEY INSIGHTS
- Reverse Linked List: save `current->next` before changing the pointer, or
  the rest of the list will be lost.
- Merge Two Sorted Lists: because both lists are already sorted, compare only
  their current nodes. No additional sorting is necessary.
- The iterative solutions reuse the existing nodes and allocate no new list
  nodes. The brute-force merge allocates a new list and does not splice nodes.

RECOMMENDED APPROACHES
- LeetCode 206: ReverseListIterative — O(n) time, O(1) auxiliary space.
- LeetCode 21: MergeTwoListsIterative — O(n+m) time, O(1) auxiliary space.

To submit on LeetCode, copy the chosen class's method into `class Solution`.
The file contains multiple classes intentionally, so all approaches can
coexist in one source file for learning and comparison.
*/
